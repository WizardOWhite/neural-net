cmake_minimum_required(VERSION 3.24)
project(BasicNeuralNet)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SOURCES main.cpp Classes/NeuralNet.cpp Classes/Node.cpp Classes/DataInputFile.cpp)
elseif (CMAKE_BUILD_TYPE STREQUAL "Secondary")
    set(SOURCES NeuralNet2.cpp)
else()
    message(FATAL_ERROR "Unsupported build type: ${CMAKE_BUILD_TYPE}")
endif()

add_executable(BasicNeuralNet ${SOURCES})