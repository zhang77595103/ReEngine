cmake_minimum_required(VERSION 3.6)
project(ReEngine)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp NFA_Node.cpp NFA_Node.h Edge.h NFA.cpp NFA.h MemPool.cpp MemPool.h DFA.cpp DFA.h DFA_Node.cpp DFA_Node.h)
add_executable(ReEngine ${SOURCE_FILES})