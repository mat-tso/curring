
// An atempt of reimplementing a simple bind in c++03

// Curried forme of a 0 arg function (prety much useless ;)
template <typename Ret>
class Curried0p
{
public:
	typedef Ret F();

	Curried0p(F f) : _f(f) {}

	Ret operator() () {
		return _f();
	}
	F *_f;
};

// Bind for simple function of 0 arg
template <typename Ret>
Curried0p<Ret> bind(Ret f()) {
	return Curried0p<Ret>(f);
}

// Curried forme of a 0 arg method (much more usefull :)
template <typename Ret, class C>
class Curried0o
{
public:
	typedef Ret (C::*M)();

	Curried0o(M m, C &i): _m(m), _i(i) {}

	Ret operator() () {
		return (_i.*_m)();
	}
private:
	M _m;
	C &_i;
};

// Bind for simple method of 0 arg
template <typename Ret, class C>
Curried0o<Ret, C> bind(Ret (C::*m)(), C &i) {
	return Curried0o<Ret, C>(m, i);
}

  ////////////
 ////Test////
////////////
#include <cassert>
#include <string>
#include <iostream>

using namespace std;

string lfc = "toto";

struct o0 {
	void hi() {lfc="hi";};
};

void f0 () {lfc="f0";}

bool failed = false;

void assertStr (const string str) {
	if (str != lfc)
	{
		cout << "Found " << lfc << " expecting " << str << endl;
		failed = true;
	}
	lfc = "bla bla bla";
}

int main () {
	f0();
	assertStr("f0");
	Curried0p<void> cur = bind(f0);
	cur();
	assertStr("f0");
	o0 obj;
	// Here I got too lasy to write to type :/
	auto myHi(bind(&o0::hi, obj));
	myHi();
	assertStr("hi");
	return failed ? 1 : 0;
}
