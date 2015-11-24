cmake_minimum_required(VERSION 3.3)
project(ShellPipe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SHELLPIPE ShellPipe.cpp ShellPipe.h)

add_executable(prompt prompt.cpp ${SHELLPIPE})