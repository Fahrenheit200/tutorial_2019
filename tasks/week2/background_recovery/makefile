LIBS = `pkg-config --cflags --libs opencv`

./bin/dmeo: ./build/Recovery.o
	g++ -o ./bin/demo ./build/Recovery.o $(LIBS)

./build/Recovery.o: ./src/Recovery.cpp ./include/Recovery.h
	g++ -c ./src/Recovery.cpp -o ./build/Recovery.o $(LIBS)

clean:
	rm -rf ./build/*.o ./bin/demo
