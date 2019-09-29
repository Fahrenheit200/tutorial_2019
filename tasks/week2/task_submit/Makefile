LIB_PATH = /usr/local/lib
INC_PATH = include/:/usr/local/include/opencv4/
LIB_FILE = -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_videoio
scbg5: scbg5.cpp recovery/build/timer.o
	g++ -O2	scbg5.cpp ${LIB_FILE} -o scbg5 -Irecovery/include/ recovery/build/timer.o
recovery/build/timer.o: recovery/src/timer.cpp recovery/include/timer.h
	g++ -c recovery/src/timer.cpp -Irecovery/include/ -o recovery/build/timer.o
