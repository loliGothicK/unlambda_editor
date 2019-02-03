#include <iostream>

class function{
	function *parent, *left, *right;
	char name;
	enum class Type { application, combinator, character, input, character_input } type;
public:
	function(function * = nullptr);
	~function();
	function *move(int);
	void show(function *cursor);

	friend std::ostream &operator<<(std::ostream &, const function &);
	friend std::istream &operator>>(std::istream &, function &);

	friend std::ostream &operator<<(std::ostream &os, const function &fnc){
		switch(fnc.type){
			case Type::application:
				return os << '`' << *fnc.left << *fnc.right;
			case Type::character:
				os << '.';
			case Type::combinator:
				return os << fnc.name;
			default:
				return os << 'i';
		}
	}

	friend std::istream &operator>>(std::istream &is, function &fnc){
		char ch;
		is >> ch;
		if(ch == '`'){
			fnc.type = Type::application;
			fnc.left = new function(&fnc);
			fnc.right = new function(&fnc);
			is >> *fnc.left >> *fnc.right;
		}else if(ch == '.'){
			fnc.type = Type::character;
			is >> ch;
			fnc.name = ch;
		}else{
			fnc.type = Type::combinator;
			fnc.name = ch;
		}
		return is;
	}
};

