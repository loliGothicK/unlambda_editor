#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include "function.h"

int main(int argc, char *argv[]){
	initscr();
	function mainfnc, *cursor = &mainfnc;
	cbreak();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	if(argc > 1){
		std::ifstream file(argv[1]);
		if(file) file >> mainfnc;
	}
	for(;;){
		move(0, 0);
		if(argc > 1) addstr(argv[1]);
		move(1, 0);
		mainfnc.show(cursor);
		int ch = getch();
		if(ch == 10){
			endwin();
			char filename[100];
			if(argc == 1){
				move(0, 0);
				echo();
				curs_set(TRUE);
				getstr(filename);
			}else strcpy(filename, argv[1]);
			std::ofstream file(filename);
			file << mainfnc << std::endl;
			return 0;
		}
		else cursor = cursor->move(ch);
		erase();
	}
}
