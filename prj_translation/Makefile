main : main.o translator.o
	g++ -g -o $@ main.o translator.o -lcurl

main.o : main.cpp translator.cpp translator.cpp
	g++ -c $*.cpp

translator.o : translator.cpp translator.hpp
	g++ -c $*.cpp