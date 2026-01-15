# -------- Compiler & flags --------
CXX      := g++
CC       := gcc

CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinclude
CFLAGS   := -Wall -Wextra -O2 -Iinclude

LDFLAGS  := -lglfw -lGL

# -------- Directories --------
SRC_DIR  := src
BUILD_DIR := build

# -------- Files --------
TARGET   := build/boom

CPP_SRCS := $(SRC_DIR)/main.cpp $(SRC_DIR)/stb_image.cpp $(SRC_DIR)/shader.cpp $(SRC_DIR)/material.cpp $(SRC_DIR)/camera.cpp $(SRC_DIR)/mesh.cpp $(SRC_DIR)/scene.cpp $(SRC_DIR)/input_handler.cpp
C_SRCS   := $(SRC_DIR)/glad.c

CPP_OBJS := $(CPP_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
C_OBJS   := $(C_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

OBJS     := $(CPP_OBJS) $(C_OBJS)

# -------- Rules --------
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile C++ sources
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C sources (GLAD)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm  $(BUILD_DIR)/*

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean

