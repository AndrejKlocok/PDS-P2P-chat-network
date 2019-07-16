# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/H365379/CLionProjects/PDS-P2P-chat-network

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/H365379/CLionProjects/PDS-P2P-chat-network

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target test
test:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running tests..."
	/usr/bin/ctest --force-new-ctest-process $(ARGS)
.PHONY : test

# Special rule for the target test
test/fast: test

.PHONY : test/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/c/Users/H365379/CLionProjects/PDS-P2P-chat-network/CMakeFiles /mnt/c/Users/H365379/CLionProjects/PDS-P2P-chat-network/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/c/Users/H365379/CLionProjects/PDS-P2P-chat-network/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named runUnitTests

# Build rule for target.
runUnitTests: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 runUnitTests
.PHONY : runUnitTests

# fast build rule for target.
runUnitTests/fast:
	$(MAKE) -f CMakeFiles/runUnitTests.dir/build.make CMakeFiles/runUnitTests.dir/build
.PHONY : runUnitTests/fast

#=============================================================================
# Target rules for targets named node_lib

# Build rule for target.
node_lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 node_lib
.PHONY : node_lib

# fast build rule for target.
node_lib/fast:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/build
.PHONY : node_lib/fast

#=============================================================================
# Target rules for targets named pds18-rpc

# Build rule for target.
pds18-rpc: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pds18-rpc
.PHONY : pds18-rpc

# fast build rule for target.
pds18-rpc/fast:
	$(MAKE) -f CMakeFiles/pds18-rpc.dir/build.make CMakeFiles/pds18-rpc.dir/build
.PHONY : pds18-rpc/fast

#=============================================================================
# Target rules for targets named common_lib

# Build rule for target.
common_lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 common_lib
.PHONY : common_lib

# fast build rule for target.
common_lib/fast:
	$(MAKE) -f CMakeFiles/common_lib.dir/build.make CMakeFiles/common_lib.dir/build
.PHONY : common_lib/fast

#=============================================================================
# Target rules for targets named pds18-peer

# Build rule for target.
pds18-peer: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pds18-peer
.PHONY : pds18-peer

# fast build rule for target.
pds18-peer/fast:
	$(MAKE) -f CMakeFiles/pds18-peer.dir/build.make CMakeFiles/pds18-peer.dir/build
.PHONY : pds18-peer/fast

#=============================================================================
# Target rules for targets named peer_lib

# Build rule for target.
peer_lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 peer_lib
.PHONY : peer_lib

# fast build rule for target.
peer_lib/fast:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/build
.PHONY : peer_lib/fast

#=============================================================================
# Target rules for targets named rpc_lib

# Build rule for target.
rpc_lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 rpc_lib
.PHONY : rpc_lib

# fast build rule for target.
rpc_lib/fast:
	$(MAKE) -f CMakeFiles/rpc_lib.dir/build.make CMakeFiles/rpc_lib.dir/build
.PHONY : rpc_lib/fast

#=============================================================================
# Target rules for targets named pds18-node

# Build rule for target.
pds18-node: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pds18-node
.PHONY : pds18-node

# fast build rule for target.
pds18-node/fast:
	$(MAKE) -f CMakeFiles/pds18-node.dir/build.make CMakeFiles/pds18-node.dir/build
.PHONY : pds18-node/fast

#=============================================================================
# Target rules for targets named gmock_main

# Build rule for target.
gmock_main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gmock_main
.PHONY : gmock_main

# fast build rule for target.
gmock_main/fast:
	$(MAKE) -f submodules/googletest/googlemock/CMakeFiles/gmock_main.dir/build.make submodules/googletest/googlemock/CMakeFiles/gmock_main.dir/build
.PHONY : gmock_main/fast

#=============================================================================
# Target rules for targets named gmock

# Build rule for target.
gmock: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gmock
.PHONY : gmock

# fast build rule for target.
gmock/fast:
	$(MAKE) -f submodules/googletest/googlemock/CMakeFiles/gmock.dir/build.make submodules/googletest/googlemock/CMakeFiles/gmock.dir/build
.PHONY : gmock/fast

#=============================================================================
# Target rules for targets named gtest_main

# Build rule for target.
gtest_main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gtest_main
.PHONY : gtest_main

# fast build rule for target.
gtest_main/fast:
	$(MAKE) -f submodules/googletest/googletest/CMakeFiles/gtest_main.dir/build.make submodules/googletest/googletest/CMakeFiles/gtest_main.dir/build
.PHONY : gtest_main/fast

#=============================================================================
# Target rules for targets named gtest

# Build rule for target.
gtest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gtest
.PHONY : gtest

# fast build rule for target.
gtest/fast:
	$(MAKE) -f submodules/googletest/googletest/CMakeFiles/gtest.dir/build.make submodules/googletest/googletest/CMakeFiles/gtest.dir/build
.PHONY : gtest/fast

pds18-node.o: pds18-node.cpp.o

.PHONY : pds18-node.o

# target to build an object file
pds18-node.cpp.o:
	$(MAKE) -f CMakeFiles/pds18-node.dir/build.make CMakeFiles/pds18-node.dir/pds18-node.cpp.o
.PHONY : pds18-node.cpp.o

pds18-node.i: pds18-node.cpp.i

.PHONY : pds18-node.i

# target to preprocess a source file
pds18-node.cpp.i:
	$(MAKE) -f CMakeFiles/pds18-node.dir/build.make CMakeFiles/pds18-node.dir/pds18-node.cpp.i
.PHONY : pds18-node.cpp.i

pds18-node.s: pds18-node.cpp.s

.PHONY : pds18-node.s

# target to generate assembly for a file
pds18-node.cpp.s:
	$(MAKE) -f CMakeFiles/pds18-node.dir/build.make CMakeFiles/pds18-node.dir/pds18-node.cpp.s
.PHONY : pds18-node.cpp.s

pds18-peer.o: pds18-peer.cpp.o

.PHONY : pds18-peer.o

# target to build an object file
pds18-peer.cpp.o:
	$(MAKE) -f CMakeFiles/pds18-peer.dir/build.make CMakeFiles/pds18-peer.dir/pds18-peer.cpp.o
.PHONY : pds18-peer.cpp.o

pds18-peer.i: pds18-peer.cpp.i

.PHONY : pds18-peer.i

# target to preprocess a source file
pds18-peer.cpp.i:
	$(MAKE) -f CMakeFiles/pds18-peer.dir/build.make CMakeFiles/pds18-peer.dir/pds18-peer.cpp.i
.PHONY : pds18-peer.cpp.i

pds18-peer.s: pds18-peer.cpp.s

.PHONY : pds18-peer.s

# target to generate assembly for a file
pds18-peer.cpp.s:
	$(MAKE) -f CMakeFiles/pds18-peer.dir/build.make CMakeFiles/pds18-peer.dir/pds18-peer.cpp.s
.PHONY : pds18-peer.cpp.s

pds18-rpc.o: pds18-rpc.cpp.o

.PHONY : pds18-rpc.o

# target to build an object file
pds18-rpc.cpp.o:
	$(MAKE) -f CMakeFiles/pds18-rpc.dir/build.make CMakeFiles/pds18-rpc.dir/pds18-rpc.cpp.o
.PHONY : pds18-rpc.cpp.o

pds18-rpc.i: pds18-rpc.cpp.i

.PHONY : pds18-rpc.i

# target to preprocess a source file
pds18-rpc.cpp.i:
	$(MAKE) -f CMakeFiles/pds18-rpc.dir/build.make CMakeFiles/pds18-rpc.dir/pds18-rpc.cpp.i
.PHONY : pds18-rpc.cpp.i

pds18-rpc.s: pds18-rpc.cpp.s

.PHONY : pds18-rpc.s

# target to generate assembly for a file
pds18-rpc.cpp.s:
	$(MAKE) -f CMakeFiles/pds18-rpc.dir/build.make CMakeFiles/pds18-rpc.dir/pds18-rpc.cpp.s
.PHONY : pds18-rpc.cpp.s

src/common/Bencoder.o: src/common/Bencoder.cpp.o

.PHONY : src/common/Bencoder.o

# target to build an object file
src/common/Bencoder.cpp.o:
	$(MAKE) -f CMakeFiles/common_lib.dir/build.make CMakeFiles/common_lib.dir/src/common/Bencoder.cpp.o
.PHONY : src/common/Bencoder.cpp.o

src/common/Bencoder.i: src/common/Bencoder.cpp.i

.PHONY : src/common/Bencoder.i

# target to preprocess a source file
src/common/Bencoder.cpp.i:
	$(MAKE) -f CMakeFiles/common_lib.dir/build.make CMakeFiles/common_lib.dir/src/common/Bencoder.cpp.i
.PHONY : src/common/Bencoder.cpp.i

src/common/Bencoder.s: src/common/Bencoder.cpp.s

.PHONY : src/common/Bencoder.s

# target to generate assembly for a file
src/common/Bencoder.cpp.s:
	$(MAKE) -f CMakeFiles/common_lib.dir/build.make CMakeFiles/common_lib.dir/src/common/Bencoder.cpp.s
.PHONY : src/common/Bencoder.cpp.s

src/common/ErrHandle.o: src/common/ErrHandle.cpp.o

.PHONY : src/common/ErrHandle.o

# target to build an object file
src/common/ErrHandle.cpp.o:
	$(MAKE) -f CMakeFiles/common_lib.dir/build.make CMakeFiles/common_lib.dir/src/common/ErrHandle.cpp.o
.PHONY : src/common/ErrHandle.cpp.o

src/common/ErrHandle.i: src/common/ErrHandle.cpp.i

.PHONY : src/common/ErrHandle.i

# target to preprocess a source file
src/common/ErrHandle.cpp.i:
	$(MAKE) -f CMakeFiles/common_lib.dir/build.make CMakeFiles/common_lib.dir/src/common/ErrHandle.cpp.i
.PHONY : src/common/ErrHandle.cpp.i

src/common/ErrHandle.s: src/common/ErrHandle.cpp.s

.PHONY : src/common/ErrHandle.s

# target to generate assembly for a file
src/common/ErrHandle.cpp.s:
	$(MAKE) -f CMakeFiles/common_lib.dir/build.make CMakeFiles/common_lib.dir/src/common/ErrHandle.cpp.s
.PHONY : src/common/ErrHandle.cpp.s

src/common/FileOperations.o: src/common/FileOperations.cpp.o

.PHONY : src/common/FileOperations.o

# target to build an object file
src/common/FileOperations.cpp.o:
	$(MAKE) -f CMakeFiles/common_lib.dir/build.make CMakeFiles/common_lib.dir/src/common/FileOperations.cpp.o
.PHONY : src/common/FileOperations.cpp.o

src/common/FileOperations.i: src/common/FileOperations.cpp.i

.PHONY : src/common/FileOperations.i

# target to preprocess a source file
src/common/FileOperations.cpp.i:
	$(MAKE) -f CMakeFiles/common_lib.dir/build.make CMakeFiles/common_lib.dir/src/common/FileOperations.cpp.i
.PHONY : src/common/FileOperations.cpp.i

src/common/FileOperations.s: src/common/FileOperations.cpp.s

.PHONY : src/common/FileOperations.s

# target to generate assembly for a file
src/common/FileOperations.cpp.s:
	$(MAKE) -f CMakeFiles/common_lib.dir/build.make CMakeFiles/common_lib.dir/src/common/FileOperations.cpp.s
.PHONY : src/common/FileOperations.cpp.s

src/common/Socket.o: src/common/Socket.cpp.o

.PHONY : src/common/Socket.o

# target to build an object file
src/common/Socket.cpp.o:
	$(MAKE) -f CMakeFiles/common_lib.dir/build.make CMakeFiles/common_lib.dir/src/common/Socket.cpp.o
.PHONY : src/common/Socket.cpp.o

src/common/Socket.i: src/common/Socket.cpp.i

.PHONY : src/common/Socket.i

# target to preprocess a source file
src/common/Socket.cpp.i:
	$(MAKE) -f CMakeFiles/common_lib.dir/build.make CMakeFiles/common_lib.dir/src/common/Socket.cpp.i
.PHONY : src/common/Socket.cpp.i

src/common/Socket.s: src/common/Socket.cpp.s

.PHONY : src/common/Socket.s

# target to generate assembly for a file
src/common/Socket.cpp.s:
	$(MAKE) -f CMakeFiles/common_lib.dir/build.make CMakeFiles/common_lib.dir/src/common/Socket.cpp.s
.PHONY : src/common/Socket.cpp.s

src/node/Node.o: src/node/Node.cpp.o

.PHONY : src/node/Node.o

# target to build an object file
src/node/Node.cpp.o:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/Node.cpp.o
.PHONY : src/node/Node.cpp.o

src/node/Node.i: src/node/Node.cpp.i

.PHONY : src/node/Node.i

# target to preprocess a source file
src/node/Node.cpp.i:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/Node.cpp.i
.PHONY : src/node/Node.cpp.i

src/node/Node.s: src/node/Node.cpp.s

.PHONY : src/node/Node.s

# target to generate assembly for a file
src/node/Node.cpp.s:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/Node.cpp.s
.PHONY : src/node/Node.cpp.s

src/node/NodeFunctions.o: src/node/NodeFunctions.cpp.o

.PHONY : src/node/NodeFunctions.o

# target to build an object file
src/node/NodeFunctions.cpp.o:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/NodeFunctions.cpp.o
.PHONY : src/node/NodeFunctions.cpp.o

src/node/NodeFunctions.i: src/node/NodeFunctions.cpp.i

.PHONY : src/node/NodeFunctions.i

# target to preprocess a source file
src/node/NodeFunctions.cpp.i:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/NodeFunctions.cpp.i
.PHONY : src/node/NodeFunctions.cpp.i

src/node/NodeFunctions.s: src/node/NodeFunctions.cpp.s

.PHONY : src/node/NodeFunctions.s

# target to generate assembly for a file
src/node/NodeFunctions.cpp.s:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/NodeFunctions.cpp.s
.PHONY : src/node/NodeFunctions.cpp.s

src/node/NodeHandle.o: src/node/NodeHandle.cpp.o

.PHONY : src/node/NodeHandle.o

# target to build an object file
src/node/NodeHandle.cpp.o:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/NodeHandle.cpp.o
.PHONY : src/node/NodeHandle.cpp.o

src/node/NodeHandle.i: src/node/NodeHandle.cpp.i

.PHONY : src/node/NodeHandle.i

# target to preprocess a source file
src/node/NodeHandle.cpp.i:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/NodeHandle.cpp.i
.PHONY : src/node/NodeHandle.cpp.i

src/node/NodeHandle.s: src/node/NodeHandle.cpp.s

.PHONY : src/node/NodeHandle.s

# target to generate assembly for a file
src/node/NodeHandle.cpp.s:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/NodeHandle.cpp.s
.PHONY : src/node/NodeHandle.cpp.s

src/node/NodeServer.o: src/node/NodeServer.cpp.o

.PHONY : src/node/NodeServer.o

# target to build an object file
src/node/NodeServer.cpp.o:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/NodeServer.cpp.o
.PHONY : src/node/NodeServer.cpp.o

src/node/NodeServer.i: src/node/NodeServer.cpp.i

.PHONY : src/node/NodeServer.i

# target to preprocess a source file
src/node/NodeServer.cpp.i:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/NodeServer.cpp.i
.PHONY : src/node/NodeServer.cpp.i

src/node/NodeServer.s: src/node/NodeServer.cpp.s

.PHONY : src/node/NodeServer.s

# target to generate assembly for a file
src/node/NodeServer.cpp.s:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/NodeServer.cpp.s
.PHONY : src/node/NodeServer.cpp.s

src/node/NodeStorage.o: src/node/NodeStorage.cpp.o

.PHONY : src/node/NodeStorage.o

# target to build an object file
src/node/NodeStorage.cpp.o:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/NodeStorage.cpp.o
.PHONY : src/node/NodeStorage.cpp.o

src/node/NodeStorage.i: src/node/NodeStorage.cpp.i

.PHONY : src/node/NodeStorage.i

# target to preprocess a source file
src/node/NodeStorage.cpp.i:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/NodeStorage.cpp.i
.PHONY : src/node/NodeStorage.cpp.i

src/node/NodeStorage.s: src/node/NodeStorage.cpp.s

.PHONY : src/node/NodeStorage.s

# target to generate assembly for a file
src/node/NodeStorage.cpp.s:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/NodeStorage.cpp.s
.PHONY : src/node/NodeStorage.cpp.s

src/node/RpcFunctions.o: src/node/RpcFunctions.cpp.o

.PHONY : src/node/RpcFunctions.o

# target to build an object file
src/node/RpcFunctions.cpp.o:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/RpcFunctions.cpp.o
.PHONY : src/node/RpcFunctions.cpp.o

src/node/RpcFunctions.i: src/node/RpcFunctions.cpp.i

.PHONY : src/node/RpcFunctions.i

# target to preprocess a source file
src/node/RpcFunctions.cpp.i:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/RpcFunctions.cpp.i
.PHONY : src/node/RpcFunctions.cpp.i

src/node/RpcFunctions.s: src/node/RpcFunctions.cpp.s

.PHONY : src/node/RpcFunctions.s

# target to generate assembly for a file
src/node/RpcFunctions.cpp.s:
	$(MAKE) -f CMakeFiles/node_lib.dir/build.make CMakeFiles/node_lib.dir/src/node/RpcFunctions.cpp.s
.PHONY : src/node/RpcFunctions.cpp.s

src/peer/Peer.o: src/peer/Peer.cpp.o

.PHONY : src/peer/Peer.o

# target to build an object file
src/peer/Peer.cpp.o:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/Peer.cpp.o
.PHONY : src/peer/Peer.cpp.o

src/peer/Peer.i: src/peer/Peer.cpp.i

.PHONY : src/peer/Peer.i

# target to preprocess a source file
src/peer/Peer.cpp.i:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/Peer.cpp.i
.PHONY : src/peer/Peer.cpp.i

src/peer/Peer.s: src/peer/Peer.cpp.s

.PHONY : src/peer/Peer.s

# target to generate assembly for a file
src/peer/Peer.cpp.s:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/Peer.cpp.s
.PHONY : src/peer/Peer.cpp.s

src/peer/PeerFunctions.o: src/peer/PeerFunctions.cpp.o

.PHONY : src/peer/PeerFunctions.o

# target to build an object file
src/peer/PeerFunctions.cpp.o:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/PeerFunctions.cpp.o
.PHONY : src/peer/PeerFunctions.cpp.o

src/peer/PeerFunctions.i: src/peer/PeerFunctions.cpp.i

.PHONY : src/peer/PeerFunctions.i

# target to preprocess a source file
src/peer/PeerFunctions.cpp.i:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/PeerFunctions.cpp.i
.PHONY : src/peer/PeerFunctions.cpp.i

src/peer/PeerFunctions.s: src/peer/PeerFunctions.cpp.s

.PHONY : src/peer/PeerFunctions.s

# target to generate assembly for a file
src/peer/PeerFunctions.cpp.s:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/PeerFunctions.cpp.s
.PHONY : src/peer/PeerFunctions.cpp.s

src/peer/PeerHandle.o: src/peer/PeerHandle.cpp.o

.PHONY : src/peer/PeerHandle.o

# target to build an object file
src/peer/PeerHandle.cpp.o:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/PeerHandle.cpp.o
.PHONY : src/peer/PeerHandle.cpp.o

src/peer/PeerHandle.i: src/peer/PeerHandle.cpp.i

.PHONY : src/peer/PeerHandle.i

# target to preprocess a source file
src/peer/PeerHandle.cpp.i:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/PeerHandle.cpp.i
.PHONY : src/peer/PeerHandle.cpp.i

src/peer/PeerHandle.s: src/peer/PeerHandle.cpp.s

.PHONY : src/peer/PeerHandle.s

# target to generate assembly for a file
src/peer/PeerHandle.cpp.s:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/PeerHandle.cpp.s
.PHONY : src/peer/PeerHandle.cpp.s

src/peer/PeerServer.o: src/peer/PeerServer.cpp.o

.PHONY : src/peer/PeerServer.o

# target to build an object file
src/peer/PeerServer.cpp.o:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/PeerServer.cpp.o
.PHONY : src/peer/PeerServer.cpp.o

src/peer/PeerServer.i: src/peer/PeerServer.cpp.i

.PHONY : src/peer/PeerServer.i

# target to preprocess a source file
src/peer/PeerServer.cpp.i:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/PeerServer.cpp.i
.PHONY : src/peer/PeerServer.cpp.i

src/peer/PeerServer.s: src/peer/PeerServer.cpp.s

.PHONY : src/peer/PeerServer.s

# target to generate assembly for a file
src/peer/PeerServer.cpp.s:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/PeerServer.cpp.s
.PHONY : src/peer/PeerServer.cpp.s

src/peer/PeerStorage.o: src/peer/PeerStorage.cpp.o

.PHONY : src/peer/PeerStorage.o

# target to build an object file
src/peer/PeerStorage.cpp.o:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/PeerStorage.cpp.o
.PHONY : src/peer/PeerStorage.cpp.o

src/peer/PeerStorage.i: src/peer/PeerStorage.cpp.i

.PHONY : src/peer/PeerStorage.i

# target to preprocess a source file
src/peer/PeerStorage.cpp.i:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/PeerStorage.cpp.i
.PHONY : src/peer/PeerStorage.cpp.i

src/peer/PeerStorage.s: src/peer/PeerStorage.cpp.s

.PHONY : src/peer/PeerStorage.s

# target to generate assembly for a file
src/peer/PeerStorage.cpp.s:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/PeerStorage.cpp.s
.PHONY : src/peer/PeerStorage.cpp.s

src/peer/RpcFunctions.o: src/peer/RpcFunctions.cpp.o

.PHONY : src/peer/RpcFunctions.o

# target to build an object file
src/peer/RpcFunctions.cpp.o:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/RpcFunctions.cpp.o
.PHONY : src/peer/RpcFunctions.cpp.o

src/peer/RpcFunctions.i: src/peer/RpcFunctions.cpp.i

.PHONY : src/peer/RpcFunctions.i

# target to preprocess a source file
src/peer/RpcFunctions.cpp.i:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/RpcFunctions.cpp.i
.PHONY : src/peer/RpcFunctions.cpp.i

src/peer/RpcFunctions.s: src/peer/RpcFunctions.cpp.s

.PHONY : src/peer/RpcFunctions.s

# target to generate assembly for a file
src/peer/RpcFunctions.cpp.s:
	$(MAKE) -f CMakeFiles/peer_lib.dir/build.make CMakeFiles/peer_lib.dir/src/peer/RpcFunctions.cpp.s
.PHONY : src/peer/RpcFunctions.cpp.s

src/rpc/RpcHandle.o: src/rpc/RpcHandle.cpp.o

.PHONY : src/rpc/RpcHandle.o

# target to build an object file
src/rpc/RpcHandle.cpp.o:
	$(MAKE) -f CMakeFiles/rpc_lib.dir/build.make CMakeFiles/rpc_lib.dir/src/rpc/RpcHandle.cpp.o
.PHONY : src/rpc/RpcHandle.cpp.o

src/rpc/RpcHandle.i: src/rpc/RpcHandle.cpp.i

.PHONY : src/rpc/RpcHandle.i

# target to preprocess a source file
src/rpc/RpcHandle.cpp.i:
	$(MAKE) -f CMakeFiles/rpc_lib.dir/build.make CMakeFiles/rpc_lib.dir/src/rpc/RpcHandle.cpp.i
.PHONY : src/rpc/RpcHandle.cpp.i

src/rpc/RpcHandle.s: src/rpc/RpcHandle.cpp.s

.PHONY : src/rpc/RpcHandle.s

# target to generate assembly for a file
src/rpc/RpcHandle.cpp.s:
	$(MAKE) -f CMakeFiles/rpc_lib.dir/build.make CMakeFiles/rpc_lib.dir/src/rpc/RpcHandle.cpp.s
.PHONY : src/rpc/RpcHandle.cpp.s

src/rpc/RpcNodeFunctions.o: src/rpc/RpcNodeFunctions.cpp.o

.PHONY : src/rpc/RpcNodeFunctions.o

# target to build an object file
src/rpc/RpcNodeFunctions.cpp.o:
	$(MAKE) -f CMakeFiles/rpc_lib.dir/build.make CMakeFiles/rpc_lib.dir/src/rpc/RpcNodeFunctions.cpp.o
.PHONY : src/rpc/RpcNodeFunctions.cpp.o

src/rpc/RpcNodeFunctions.i: src/rpc/RpcNodeFunctions.cpp.i

.PHONY : src/rpc/RpcNodeFunctions.i

# target to preprocess a source file
src/rpc/RpcNodeFunctions.cpp.i:
	$(MAKE) -f CMakeFiles/rpc_lib.dir/build.make CMakeFiles/rpc_lib.dir/src/rpc/RpcNodeFunctions.cpp.i
.PHONY : src/rpc/RpcNodeFunctions.cpp.i

src/rpc/RpcNodeFunctions.s: src/rpc/RpcNodeFunctions.cpp.s

.PHONY : src/rpc/RpcNodeFunctions.s

# target to generate assembly for a file
src/rpc/RpcNodeFunctions.cpp.s:
	$(MAKE) -f CMakeFiles/rpc_lib.dir/build.make CMakeFiles/rpc_lib.dir/src/rpc/RpcNodeFunctions.cpp.s
.PHONY : src/rpc/RpcNodeFunctions.cpp.s

src/rpc/RpcPeerFunctions.o: src/rpc/RpcPeerFunctions.cpp.o

.PHONY : src/rpc/RpcPeerFunctions.o

# target to build an object file
src/rpc/RpcPeerFunctions.cpp.o:
	$(MAKE) -f CMakeFiles/rpc_lib.dir/build.make CMakeFiles/rpc_lib.dir/src/rpc/RpcPeerFunctions.cpp.o
.PHONY : src/rpc/RpcPeerFunctions.cpp.o

src/rpc/RpcPeerFunctions.i: src/rpc/RpcPeerFunctions.cpp.i

.PHONY : src/rpc/RpcPeerFunctions.i

# target to preprocess a source file
src/rpc/RpcPeerFunctions.cpp.i:
	$(MAKE) -f CMakeFiles/rpc_lib.dir/build.make CMakeFiles/rpc_lib.dir/src/rpc/RpcPeerFunctions.cpp.i
.PHONY : src/rpc/RpcPeerFunctions.cpp.i

src/rpc/RpcPeerFunctions.s: src/rpc/RpcPeerFunctions.cpp.s

.PHONY : src/rpc/RpcPeerFunctions.s

# target to generate assembly for a file
src/rpc/RpcPeerFunctions.cpp.s:
	$(MAKE) -f CMakeFiles/rpc_lib.dir/build.make CMakeFiles/rpc_lib.dir/src/rpc/RpcPeerFunctions.cpp.s
.PHONY : src/rpc/RpcPeerFunctions.cpp.s

test/Bencoder_test.o: test/Bencoder_test.cpp.o

.PHONY : test/Bencoder_test.o

# target to build an object file
test/Bencoder_test.cpp.o:
	$(MAKE) -f CMakeFiles/runUnitTests.dir/build.make CMakeFiles/runUnitTests.dir/test/Bencoder_test.cpp.o
.PHONY : test/Bencoder_test.cpp.o

test/Bencoder_test.i: test/Bencoder_test.cpp.i

.PHONY : test/Bencoder_test.i

# target to preprocess a source file
test/Bencoder_test.cpp.i:
	$(MAKE) -f CMakeFiles/runUnitTests.dir/build.make CMakeFiles/runUnitTests.dir/test/Bencoder_test.cpp.i
.PHONY : test/Bencoder_test.cpp.i

test/Bencoder_test.s: test/Bencoder_test.cpp.s

.PHONY : test/Bencoder_test.s

# target to generate assembly for a file
test/Bencoder_test.cpp.s:
	$(MAKE) -f CMakeFiles/runUnitTests.dir/build.make CMakeFiles/runUnitTests.dir/test/Bencoder_test.cpp.s
.PHONY : test/Bencoder_test.cpp.s

test/Socket_test.o: test/Socket_test.cpp.o

.PHONY : test/Socket_test.o

# target to build an object file
test/Socket_test.cpp.o:
	$(MAKE) -f CMakeFiles/runUnitTests.dir/build.make CMakeFiles/runUnitTests.dir/test/Socket_test.cpp.o
.PHONY : test/Socket_test.cpp.o

test/Socket_test.i: test/Socket_test.cpp.i

.PHONY : test/Socket_test.i

# target to preprocess a source file
test/Socket_test.cpp.i:
	$(MAKE) -f CMakeFiles/runUnitTests.dir/build.make CMakeFiles/runUnitTests.dir/test/Socket_test.cpp.i
.PHONY : test/Socket_test.cpp.i

test/Socket_test.s: test/Socket_test.cpp.s

.PHONY : test/Socket_test.s

# target to generate assembly for a file
test/Socket_test.cpp.s:
	$(MAKE) -f CMakeFiles/runUnitTests.dir/build.make CMakeFiles/runUnitTests.dir/test/Socket_test.cpp.s
.PHONY : test/Socket_test.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... install/strip"
	@echo "... install"
	@echo "... install/local"
	@echo "... test"
	@echo "... list_install_components"
	@echo "... runUnitTests"
	@echo "... node_lib"
	@echo "... pds18-rpc"
	@echo "... common_lib"
	@echo "... pds18-peer"
	@echo "... edit_cache"
	@echo "... peer_lib"
	@echo "... rpc_lib"
	@echo "... rebuild_cache"
	@echo "... pds18-node"
	@echo "... gmock_main"
	@echo "... gmock"
	@echo "... gtest_main"
	@echo "... gtest"
	@echo "... pds18-node.o"
	@echo "... pds18-node.i"
	@echo "... pds18-node.s"
	@echo "... pds18-peer.o"
	@echo "... pds18-peer.i"
	@echo "... pds18-peer.s"
	@echo "... pds18-rpc.o"
	@echo "... pds18-rpc.i"
	@echo "... pds18-rpc.s"
	@echo "... src/common/Bencoder.o"
	@echo "... src/common/Bencoder.i"
	@echo "... src/common/Bencoder.s"
	@echo "... src/common/ErrHandle.o"
	@echo "... src/common/ErrHandle.i"
	@echo "... src/common/ErrHandle.s"
	@echo "... src/common/FileOperations.o"
	@echo "... src/common/FileOperations.i"
	@echo "... src/common/FileOperations.s"
	@echo "... src/common/Socket.o"
	@echo "... src/common/Socket.i"
	@echo "... src/common/Socket.s"
	@echo "... src/node/Node.o"
	@echo "... src/node/Node.i"
	@echo "... src/node/Node.s"
	@echo "... src/node/NodeFunctions.o"
	@echo "... src/node/NodeFunctions.i"
	@echo "... src/node/NodeFunctions.s"
	@echo "... src/node/NodeHandle.o"
	@echo "... src/node/NodeHandle.i"
	@echo "... src/node/NodeHandle.s"
	@echo "... src/node/NodeServer.o"
	@echo "... src/node/NodeServer.i"
	@echo "... src/node/NodeServer.s"
	@echo "... src/node/NodeStorage.o"
	@echo "... src/node/NodeStorage.i"
	@echo "... src/node/NodeStorage.s"
	@echo "... src/node/RpcFunctions.o"
	@echo "... src/node/RpcFunctions.i"
	@echo "... src/node/RpcFunctions.s"
	@echo "... src/peer/Peer.o"
	@echo "... src/peer/Peer.i"
	@echo "... src/peer/Peer.s"
	@echo "... src/peer/PeerFunctions.o"
	@echo "... src/peer/PeerFunctions.i"
	@echo "... src/peer/PeerFunctions.s"
	@echo "... src/peer/PeerHandle.o"
	@echo "... src/peer/PeerHandle.i"
	@echo "... src/peer/PeerHandle.s"
	@echo "... src/peer/PeerServer.o"
	@echo "... src/peer/PeerServer.i"
	@echo "... src/peer/PeerServer.s"
	@echo "... src/peer/PeerStorage.o"
	@echo "... src/peer/PeerStorage.i"
	@echo "... src/peer/PeerStorage.s"
	@echo "... src/peer/RpcFunctions.o"
	@echo "... src/peer/RpcFunctions.i"
	@echo "... src/peer/RpcFunctions.s"
	@echo "... src/rpc/RpcHandle.o"
	@echo "... src/rpc/RpcHandle.i"
	@echo "... src/rpc/RpcHandle.s"
	@echo "... src/rpc/RpcNodeFunctions.o"
	@echo "... src/rpc/RpcNodeFunctions.i"
	@echo "... src/rpc/RpcNodeFunctions.s"
	@echo "... src/rpc/RpcPeerFunctions.o"
	@echo "... src/rpc/RpcPeerFunctions.i"
	@echo "... src/rpc/RpcPeerFunctions.s"
	@echo "... test/Bencoder_test.o"
	@echo "... test/Bencoder_test.i"
	@echo "... test/Bencoder_test.s"
	@echo "... test/Socket_test.o"
	@echo "... test/Socket_test.i"
	@echo "... test/Socket_test.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

