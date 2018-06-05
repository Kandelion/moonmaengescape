main : main.o ocr.o translator.o
	g++ -o $@.out -I/usr/include/python2.7 main.o ocr.o translator.o -lpython2.7 -lcurl -std=c++11 -pthread `pkg-config --cflags --libs gtk+-3.0`

main.o : main.cpp ocr.cpp ocr.py ocr.hpp translator.cpp translator.cpp output.cpp output.hpp
	g++ -c $*.cpp -I/usr/include/python2.7 -std=c++11 -pthread

ocr.o : ocr.cpp ocr.py ocr.hpp
	g++ -c $*.cpp -I/usr/include/python2.7

translator.o : translator.cpp translator.hpp
	g++ -c $*.cpp

output.o : output.cpp output.hpp
	g++ -c $*.cpp `pkg-config --cflags --libs gtk+-3.0`