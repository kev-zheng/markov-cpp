# Makefile for EECS 280 Machine Learning Project

debug_or_optimize = -O1

CXX = g++
CXXFLAGS = -Wall -Werror -pedantic --std=c++11 $(debug_or_optimize)

tree_test_srcs = $(wildcard BinarySearchTree_test*.cpp)
tree_test_exes = $(tree_test_srcs:.cpp=.exe)

markov: markov.cpp
	$(CXX) $(CXXFLAGS) $ markov.cpp -o $@

# disable built-in rules
.SUFFIXES:

# these targets do not create any files
.PHONY: clean
clean :
	rm -vrf *.o *.exe *.gch *.dSYM *.out.txt main
