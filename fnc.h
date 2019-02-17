#ifndef FNC_HPP
#define FNC_HPP

class Fnc{
	Fnc *par, **ths;
	virtual void _show(Fnc *) = 0;
protected:
	Fnc(Fnc *par, Fnc **ths): par(par), ths(ths) {}
public:
	Fnc *parent();
	virtual Fnc *child_left() = 0, *child_right() = 0;
	Fnc *brother_left(), *brother_right();
	Fnc *insert_left(), *insert_right();
	Fnc *com(char), *app(char, char);
	void show(Fnc *);
	virtual ~Fnc() {}
};

class Com final : public Fnc{
	const char text;
	void _show(Fnc *);
	~Com();
public:
	Com(Fnc *, Fnc **, char);
	virtual Fnc *child_left(), *child_right() override final;
};

class App final : public Fnc{
	Fnc *lft, *rgt;
	void _show(Fnc *);
	~App();
	App(Fnc *, Fnc **, Fnc *, Fnc *);
	App(Fnc *, Fnc **, char, char);
	friend Fnc *Fnc::app(char, char);
public:
	Fnc *child_left(), *child_right();
};

#endif