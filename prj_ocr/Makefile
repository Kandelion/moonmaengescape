main : main.o ocr.o
	g++ -o $@.out -I/usr/include/python2.7 main.o ocr.o -lpython2.7

main.o : main.cpp ocr.cpp ocr.py ocr.hpp
	g++ -c $*.cpp

ocr.o : ocr.cpp ocr.py ocr.hpp
	g++ -c $*.cpp