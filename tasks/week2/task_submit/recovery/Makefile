LIB_PATH = /usr/local/lib
INC_PATH = include/:/usr/local/include/opencv4/
LIB_FILE = -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_core
bin/recovery: build/main.o build/Recovery.o
	g++ build/*.o ${LIB_FILE} -o bin/recovery
build/main.o: src/main.cpp
	g++ src/main.cpp -c -I${INC_PATH} -o build/main.o
build/Recovery.o: src/Recovery.cpp include/Recovery.h
	g++ src/Recovery.cpp -c -I${INC_PATH} -o build/Recovery.o
