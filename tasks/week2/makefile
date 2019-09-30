LIBS = `pkg-config  --cflags  --libs opencv`

./bin/Recovery_test : 	./bulid/Recovery.o
		g++ 	-o		./bin/Recovery_test		./build/Recovery.o $(LIBS)

./bulid/Recovery.o :		./src/Recovery.cpp		./include/Recovery.hpp
		g++		-c		./src/Recovery.cpp 		-o		./build/Recovery.o	-Iinclude

.PHONY : clean
clean :
	rm ./bin/*
