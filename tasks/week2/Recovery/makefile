main: test.o Recovery.o 
	g++ test.o Recovery.o -o main `pkg-config --cflags --libs opencv`

Recovery.o: Recovery.h Recovery.cpp 
	g++ -c Recovery.cpp `pkg-config --cflags --libs opencv`

test.o: test.cpp 
	g++ -c test.cpp `pkg-config --cflags --libs opencv`
