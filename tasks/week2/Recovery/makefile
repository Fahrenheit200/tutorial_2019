bin/demo: Recovery.o demo.o inc/Recovery.h
	g++ Recovery.o demo.o -o bin/demo `pkg-config --cflags --libs opencv`
Recovery.o: src/Recovery.cpp inc/Recovery.h
	g++ -c src/Recovery.cpp `pkg-config --cflags --libs opencv`
demo.o: test/demo.cpp inc/Recovery.h
	g++ -c test/demo.cpp
