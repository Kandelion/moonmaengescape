main : main.o output.o
	g++ -o $@.out main.o output.o `pkg-config --cflags --libs gtk+-3.0` 

main.o : main.cpp output.cpp output.hpp
	g++ -c $*.cpp `pkg-config --cflags --libs gtk+-3.0`

output.o : output.cpp output.hpp
	g++ -c $*.cpp `pkg-config --cflags --libs gtk+-3.0`


#make:
	#g++ output.cpp -o output.out `pkg-config --cflags --libs gtk+-3.0`
	#g++ main.cpp -o main.out `pkg-config --cflags --libs gtk+-3.0`
	#g++ output.backup.cpp -o output.backup.out `pkg-config --cflags --libs gtk+-3.0`
#clean:
	#rm -rf output.out

#make :
	#g++ -o main.out main.cpp output.cpp `pkg-config --cflags --libs gtk+-3.0`

