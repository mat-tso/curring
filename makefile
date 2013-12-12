
# TODO use a cmakefile
curring-test : curring.hpp main.cpp
	$(CXX) --std=c++11 -Wall -Wextra -Wpedantic -Werror -o $@ main.cpp
