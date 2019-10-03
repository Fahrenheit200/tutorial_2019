CC := g++
FLAGS := -std=c++11 -w
CFLAGS := `pkg-config --cflags opencv`
LIBS := `pkg-config --libs opencv` 
INC_DIR := inc
SRC_DIR := src
BIN_DIR := bin
BUILD_DIR := build
INCLUDE:=-I./$(INC_DIR)
$(BIN_DIR)/recovery: $(BUILD_DIR)/recovery.o $(BUILD_DIR)/main.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $(BUILD_DIR)/recovery.o $(BUILD_DIR)/main.o -o $@ $(CFLAGS) $(LIBS)

$(BUILD_DIR)/main.o:$(SRC_DIR)/main.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $(SRC_DIR)/main.cpp $(CFLAGS) $(LIBS)

$(BUILD_DIR)/recovery.o: $(SRC_DIR)/recovery.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $(SRC_DIR)/recovery.cpp $(CFLAGS) $(LIBS)


