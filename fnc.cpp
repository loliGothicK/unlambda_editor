#include <curses.h>
#include "fnc.h"

Com::Com(Fnc *par, Fnc **ths, char text): Fnc(par, ths), text(text) {}
Com::~Com(){}
App::App(Fnc *par, Fnc **ths, char ltext, char rtext): Fnc(par, ths){
	lft = new Com(this, &lft, ltext);
	rgt = new Com(this, &rgt, rtext);
}
App::~App(){
	delete lft;
	delete rgt;
}

Fnc *Fnc::parent(){ return par ? par : this; }
Fnc *Fnc::brother_left(){ return par ? par->child_left() : this; }
Fnc *Fnc::brother_right(){ return par ? par->child_right() : this; }
Fnc *Com::child_left(){ return this; }
Fnc *App::child_left(){ return lft; }
Fnc *Com::child_right(){ return this; }
Fnc *App::child_right(){ return rgt; }

Fnc *Fnc::com(char text){
	*ths = new Com(par, ths, text);
	delete this;
	return *ths;
}
Fnc *Fnc::app(char ltext, char rtext){
	*ths = new App(par, ths, ltext, rtext);
	delete this;
	return *ths;
}

void Fnc::show(Fnc *cur){
	if(cur == this) standout();
	_show(cur);
	if(cur == this) standend();
}
void Com::_show(Fnc *cur [[maybe_unused]]){
	addch(text);
}
void App::_show(Fnc *cur){
	addch('`');
	lft->show(cur);
	rgt->show(cur);
}
