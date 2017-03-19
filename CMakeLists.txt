cmake_minimum_required(VERSION 3.6)
project(ReEngine)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Node.cpp Node.h Edge.cpp Edge.h NFA.cpp NFA.h MemPool.cpp MemPool.h Nodes.h)
add_executable(ReEngine ${SOURCE_FILES})