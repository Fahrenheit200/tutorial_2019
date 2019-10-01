vpath %.h include
vpath %.cpp src

bin/test.out: Recovery.o test.o
	g++ -o Recovery.o test.o src/Recovery.cpp `pkg-config --cflags --libs opencv` -std=c++11 -I include/ -o $@

Recovery.o: Recovery.h Recovery.cpp
	g++ -c src/Recovery.cpp include/Recovery.h `pkg-config --cflags --libs opencv` -std=c++11 -I include/ -I src/

test.o: test.cpp Recovery.h Recovery.cpp
	g++ -c src/test.cpp include/Recovery.h  `pkg-config --cflags --libs opencv` -std=c++11 -I src/ -I include/

