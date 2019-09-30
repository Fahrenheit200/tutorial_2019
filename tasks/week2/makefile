vpath %.h inc
vpath %.cpp test
vpath %.cpp src
bin/main.out:  Recovery.o test.o
	g++ -o  Recovery.o  test.o src/Recovery.cpp `pkg-config --cflags --libs opencv` -I inc/   -o $@
 	
Recovery.o: Recovery.h  Recovery.cpp
	g++ -c  src/Recovery.cpp  inc/Recovery.h `pkg-config --cflags --libs opencv` -I inc/ -I src/
test.o: test.cpp Recovery.h Recovery.cpp
	g++ -c  test/test.cpp inc/Recovery.h  `pkg-config --cflags --libs opencv`  -I src/ -I inc/
	
