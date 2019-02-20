LIB_SRC_DIR  = src
BUILD = build

# Set of src/inc files used in build process
HEADERS   	= $(wildcard $(LIB_SRC_DIR)/common/*.h) $(wildcard $(LIB_SRC_DIR)/rpc/*.h) 
SRC_FILES   = $(wildcard $(LIB_SRC_DIR)/common/*.cpp) $(wildcard $(LIB_SRC_DIR)/common/*.hpp) $(wildcard $(LIB_SRC_DIR)/rpc/*.cpp)

# Compiler/Linker required information
CXX      = g++
CXXFLAGS = -std=c++14 -g -I$(LIB_SRC_DIR) -Wall -pedantic #-pthread
TARGET_RPC	 = pds18-rpc


all: rpc

rpc:
	$(CXX) $(CXXFLAGS) $(SRC_FILES) pds18-rpc.cpp -o $(BUILD)/$(TARGET_RPC) 

run:
	$(BUILD)/$(TARGET_RPC) $(RUN_ARGS)
clean:
	rm --recursive --force $(BUILD)/$(TARGET_RPC)