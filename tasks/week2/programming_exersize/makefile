vpath %.h include
vpath %.cpp src

bin/test.out: addTwoNumbers.o main.o
	g++ -o addTwoNumbers.o main.o -I include/ -o $@

addTwoNumbers.o: ListNode.h addTwoNumbers.cpp
	g++ -c src/addTwoNumbers.cpp include/ListNode.h -I include/ -I src/

main.o: main.cpp addTwoNumbers.cpp ListNode.h
	g++ -c src/main.cpp include/ListNode.h -I src/ -I include/
