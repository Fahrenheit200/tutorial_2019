INC_PATH = include/
LIBS = -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lopencv_imgcodecs -lopencv_core
bin/recovery: build/main.o build/Recovery.o
	g++ build/*.o  ${LIBS} -o bin/recovery
build/main.o: src/main.cpp src/Recovery.cpp include/Recovery.h
	g++ src/main.cpp -c -I${INC_PATH} -o build/main.o
build/Recovery.o: src/Recovery.cpp include/Recovery.h
	g++ src/Recovery.cpp -c -I${INC_PATH} -o build/Recovery.o
