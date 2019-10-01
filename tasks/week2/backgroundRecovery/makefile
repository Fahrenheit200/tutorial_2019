vpath %.h include
vpath %.cpp src

bin/test.out: Recovery.o main.o
	g++ -o Recovery.o main.o `pkg-config --cflags --libs opencv` -I include/ -o $@

Recovery.o: Recovery.h Recovery.cpp
	g++ -c src/Recovery.cpp include/Recovery.h `pkg-config --cflags --libs opencv` -I include/ -I src/

main.o: main.cpp Recovery.h Recovery.cpp
	g++ -c src/main.cpp include/Recovery.h  `pkg-config --cflags --libs opencv` -I src/ -I include/

clean:
	rm ${objects}
