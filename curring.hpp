
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

// Curried forme of a 0 arg method (more usefull :)
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
