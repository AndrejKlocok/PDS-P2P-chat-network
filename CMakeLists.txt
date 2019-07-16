# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.10)

project(PDS_P2P_chat_network)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE libraries  libs/ctpl_stl.h libs/json.hpp)
file(GLOB_RECURSE common    src/common/*.cpp src/common/*.h)
file(GLOB_RECURSE node    src/node/*.cpp src/node/*.h)
file(GLOB_RECURSE peer    src/peer/*.cpp src/peer/*.h)
file(GLOB_RECURSE rpc    src/rpc/*.cpp src/rpc/*.h)

add_library(common_lib ${common} ${libraries})
add_library(node_lib  ${node})
add_library(peer_lib ${peer})
add_library(rpc_lib ${rpc} )

add_executable(pds18-peer pds18-peer.cpp)
add_executable(pds18-node pds18-node.cpp)
add_executable(pds18-rpc pds18-rpc.cpp)

target_link_libraries(pds18-peer peer_lib common_lib)
target_link_libraries(pds18-node node_lib common_lib)
target_link_libraries(pds18-rpc rpc_lib common_lib)

SET( CMAKE_CXX_FLAGS  "-std=c++17 -Wall -pedantic -pthread")

########################################
# GTest
########################################
add_subdirectory (submodules/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

########################################
# Test files
########################################
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

########################################
# Unit Tests
########################################
add_executable(runUnitTests ${TEST_SRC_FILES})

########################################
# Standard linking to gtest stuff.
########################################
target_link_libraries(runUnitTests gtest gtest_main)

########################################
# Extra linking for the project.
########################################
target_link_libraries(runUnitTests common_lib)

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(UnitTests runUnitTests)