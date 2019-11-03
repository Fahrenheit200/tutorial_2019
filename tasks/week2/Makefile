CC := g++
CCFLAGS := -Wall -std=c++14 -O2 -pthread 
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
RESULT_DIR := result
INCLUDE := -I./$(INC_DIR) 
OPENCV_INC := $(shell pkg-config --cflags opencv3)
OPENCV_LIB := $(shell pkg-config --libs opencv3)

$(BIN_DIR)/main: $(BUILD_DIR)/Recovery.o $(BUILD_DIR)/main.o
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(RESULT_DIR)
	$(CC) $(CCFLAGS) $(INCLUDE) $(OPENCV_INC) $(OPENCV_LIB) $^ -o $@
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CCFLAGS) $(INCLUDE) $(OPENCV_INC) $(OPENCV_LIB) -c -o $@ $<

.PHONY: clean
clean:
	-@rm -rf $(BUILD_DIR)
	-@rm -rf $(BIN_DIR)
