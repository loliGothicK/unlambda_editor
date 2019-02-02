#include <ostream>

enum Type { application, combinator, character, input, character_input };

class function{
	function *parent, *left, *right;
	char name;
	Type type;
public:
	function(function * = nullptr);
	~function();
	function *move(int);
	void show(function *cursor);
	friend std::ostream &operator<<(std::ostream &, const function &);
};

