#include "curring.hpp"

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
	// Here I got too lasy to write the type :/
	auto myHi(bind(&o0::hi, obj));
	myHi();
	assertStr("hi");
	return failed ? 1 : 0;
}
