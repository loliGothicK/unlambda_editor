#include <ncurses.h>
#include <iostream>
#include <fstream>
#include "function.h"

int main(int argc, char *argv[]){
	initscr();
	cbreak();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	function mainfnc, *cursor = &mainfnc;
	for(;;){
		move(0, 0);
		mainfnc.show(cursor);
		int ch = getch();
		if(ch == 10){
			endwin();
			if(argc > 1){
				std::ofstream out(argv[1]);
				out << mainfnc << std::endl;
			}
			return 0;
		}
		else cursor = cursor->move(ch);
		erase();
	}
}
