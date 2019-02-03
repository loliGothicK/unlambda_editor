#include <curses.h>
#include "function.h"

function *function::move(int ch){
	function *tmp;
	switch(type){
		case Type::application:
			switch(ch){
				case 'u':
					return left;
				case 'i':
					return right;
				case 'd':
					return parent ? parent : this;
				case 'h':
					return parent ? parent->left : this;
				case 't':
					return parent ? parent->right : this;
				case KEY_BACKSPACE:
					delete left;
					delete right;
					type = Type::input;
					break;
				case 'g':
					delete right;
					type = left->type;
					name = left->name;
					right = left->right;
					tmp = left->left;
					left->type = Type::combinator;
					delete left;
					break;
				case 'c':
					delete left;
					type = right->type;
					name = right->name;
					tmp = right->right;
					left = right->left;
					right->type = Type::combinator;
					delete right;
					break;
				case 'y':
				case 'f':
					tmp = new function(this);
					tmp->type = type;
					tmp->left = left;
					tmp->right = right;
					(ch == 'y' ? left : right) = tmp;
					(ch == 'y' ? right : left) = new function(this);
					break;
			}
			break;
		case Type::combinator:
		case Type::character:
			switch(ch){
				case 'd':
					return parent ? parent : this;
				case 'h':
					return parent ? parent->left : this;
				case 't':
					return parent ? parent->right : this;
				case KEY_BACKSPACE:
					type = Type::input;
					break;
				case 'y':
				case 'f':
					function *tmp = new function(this);
					tmp->type = type;
					tmp->name = name;
					tmp->text = text;
					type = Type::application;
					(ch == 'y' ? left : right) = tmp;
					(ch == 'y' ? right : left) = new function(this);
					break;
			}
			break;
		case Type::input:
			switch(ch){
				case 's':
				case 'k':
				case 'i':
				case 'r':
				case 'v':
				case 'c':
				case 'd':
				case 'e':
				case '@':
				case '|':
					type = Type::combinator;
					name = ch;
					break;
				case 'a':
					type = Type::application;
					left = new function(this);
					right = new function(this);
					break;
				case '.':
				case '?':
					type = Type::character_input;
					name = ch;
					break;
			}
			break;
		case Type::character_input:
			type = Type::character;
			text = ch;
			break;
	}
	return this;
}

function::function(function *parent) : parent(parent) {
	type = Type::input;
}

function::~function(){
	if(type == Type::application){
		delete left;
		delete right;
	}
}

void function::show(function *cursor){
	if(cursor == this) standout();
	switch(type){
		case Type::application:
			addch('`');
			left->show(cursor);
			right->show(cursor);
			break;
		case Type::character:
			addch(name);
			addch(text);
			break;
		case Type::combinator:
			addch(name);
			break;
		case Type::character_input:
			addch(name);
		case Type::input:
			addch('_');
			break;
	}
	if(cursor == this) standend();
}

