#include <stdio.h>
#include <curses.h>
#include "fnc.h"

enum class Command{
	none,
	quit,
	app,
	com_s,
	com_k,
	com_i,
	child_left,
	child_right,
	brother_left,
	brother_right,
	parent
} list[256];

int main(int argc, char *argv[]){
	initscr();
	Fnc *fnc = new Com(nullptr, &fnc, 'i'), *cur = fnc;
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);

	list[10] = Command::quit;
	list['a'] = Command::app;
	list['s'] = Command::com_s;
	list['k'] = Command::com_k;
	list['i'] = Command::com_i;
	list['l'] = Command::child_left;
	list['r'] = Command::child_right;
	list['l' & 037] = Command::brother_left;
	list['r' & 037] = Command::brother_right;
	list['p'] = Command::parent;

	for(;;){
		move(0, 0);
		fnc->show(cur);
		switch(list[getch()]){
			case Command::none:
				break;
			case Command::quit:
				endwin();
				return 0;
			case Command::app:
				cur = cur->app('i', 'i');
				break;
			case Command::com_s:
				cur = cur->com('s');
				break;
			case Command::com_k:
				cur = cur->com('k');
				break;
			case Command::com_i:
				cur = cur->com('i');
				break;
			case Command::child_left:
				cur = cur->child_left();
				break;
			case Command::child_right:
				cur = cur->child_right();
				break;
			case Command::brother_left:
				cur = cur->brother_left();
				break;
			case Command::brother_right:
				cur = cur->brother_right();
				break;
			case Command::parent:
				cur = cur->parent();
				break;
		}
		erase();
	}
}
