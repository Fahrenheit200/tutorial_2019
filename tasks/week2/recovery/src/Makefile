recovery.out:recovery.o
	g++ recovery.o -o recovery.out `pkg-config --libs --cflags opencv`
recovery.o: recovery.cpp recovery.h
	g++ -Wall recovery.cpp recovery.h -c
