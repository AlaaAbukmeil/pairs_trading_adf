# Compiler
CXX = g++
CXXFLAGS = -g -Wall -std=c++20 -I/usr/local/include -I/opt/homebrew/include -I/opt/homebrew/nlohmann-json 
CXXFLAGS += -I/opt/homebrew/opt/eigen/include/eigen3
CXXFLAGS += -I/opt/homebrew/opt/dlib/include

LDFLAGS = -lcurl -L/usr/local/lib -L/opt/homebrew/lib 

# Directories
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Files
SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/httpRequests.cpp $(SRC_DIR)/adf.cpp $(SRC_DIR)/tools.cpp $(SRC_DIR)/polygon.cpp
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))
TARGET = $(BIN_DIR)/main

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compiling
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean