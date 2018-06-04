main : main.o ocr.o translator.o
	g++ -g -o $@.out -I/usr/include/python2.7 main.o ocr.o translator.o -lpython2.7 -lcurl

main.o : main.cpp ocr.cpp ocr.py ocr.hpp translator.cpp translator.cpp
	g++ -g -c $*.cpp -I/usr/include/python2.7

ocr.o : ocr.cpp ocr.py ocr.hpp
	g++ -g -c $*.cpp -I/usr/include/python2.7

translator.o : translator.cpp translator.hpp
	g++ -g -c $*.cpp
