# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.10)

project(PDS_P2P_chat_network)

set(CMAKE_CXX_STANDARD 17)

#include_directories(libs)
#include_directories(src/common)
#include_directories(src/node)
#include_directories(src/peer)
#include_directories(src/rpc)

file(GLOB_RECURSE libraries  libs/ctpl_stl.h libs/json.hpp)
file(GLOB_RECURSE common    src/common/*.cpp src/common/*.h)
file(GLOB_RECURSE node    src/node/*.cpp src/node/*.h)
file(GLOB_RECURSE peer    src/peer/*.cpp src/peer/*.h)
file(GLOB_RECURSE rpc    src/rpc/*.cpp src/rpc/*.h)

add_executable(pds18-peer ${libraries} ${common} ${peer} pds18-peer.cpp)
add_executable(pds18-node ${libraries} ${common} ${node} pds18-node.cpp)
add_executable(pds18-rpc ${libraries} ${common} ${rpc} pds18-rpc.cpp)

SET( CMAKE_CXX_FLAGS  "-std=c++17 -Wall -pedantic -pthread")
