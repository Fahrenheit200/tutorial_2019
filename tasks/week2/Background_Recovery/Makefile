./bin/Recovery :./build/Recovery.o 
	g++ ./build/Recovery.o -o ./bin/Recovery `pkg-config --cflags --libs opencv`
    
./build/Recovery.o : ./src/Recovery.cpp ./include/Recovery.hpp  
	g++ -c ./src/Recovery.cpp -o ./build/Recovery.o `pkg-config --cflags --libs opencv`
clean :  
	rm -rf *.o ./bin/Recovery  
