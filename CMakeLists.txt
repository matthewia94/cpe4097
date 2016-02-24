cmake_minimum_required(VERSION 3.3)
project(cpe4097)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Joystick.cpp Joystick.h)
add_executable(cpe4097 ${SOURCE_FILES})
target_link_libraries(cpe4097 ${CMAKE_THREAD_LIBS_INIT})