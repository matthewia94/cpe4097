cmake_minimum_required(VERSION 3.3)
project(cpe4097)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system serialization)
include_directories( ${Boost_INCLUDE_DIRS} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CLIENT_SOURCE_FILES main.cpp StepperMotor.cpp StepperMotor.h GPIOClass.cpp GPIOClass.h connection.hpp client.cpp
        client.h Joystick.cpp Joystick.h rpiPWM1.cpp rpiPWM1.h Actuator.cpp Actuator.h Lawnmower.cpp Lawnmower.h)
add_executable(client ${CLIENT_SOURCE_FILES})
target_link_libraries(client ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})

set(SERVER_SOURCE_FILES server_main.cpp Joystick.cpp Joystick.h connection.hpp server.cpp server.h )
add_executable(server ${SERVER_SOURCE_FILES})
target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})