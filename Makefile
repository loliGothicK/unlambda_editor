install:
	g++ main.cpp fnc.cpp -o unlambda_editor -std=c++17 -Wall -Wextra -pedantic-errors -lncurses -Wno-return-type -O2 -march=native
