CC=g++
TARGET = $(BIN)/test

BIN = ./bin
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
DEPS_DIR = $(BUILD_DIR)/deps
RES_DIR = result
INC_DIR = -I./include

CC_FLAGS := $(INC_DIR)

DIRS := $(shell find $(SRC_DIR) -maxdepth 3 -type d)
VPATH = $(DIRS)

SOURCES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c)) 
OBJS   = $(addprefix $(OBJ_DIR)/,$(patsubst %.c,%.o,$(notdir $(SOURCES))))  
DEPS  = $(addprefix $(DEPS_DIR)/, $(patsubst %.c,%.d,$(notdir $(SOURCES)))) 
 
$(TARGET):$(OBJS)
	if [ ! -d $(RES_DIR) ]; then mkdir -p $(RES_DIR); fi;\
	$(CC) -o $@ $^ `pkg-config --cflags --libs opencv`
 
$(OBJ_DIR)/%.o:%.c
	if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi;\
	$(CC) -c $(CC_FLAGS) -o $@ $<

.PHONY : clean
clean:
	rm -rf $(TARGET) $(BUILD_DIR) $(RES_DIR)

