cmake_minimum_required(VERSION 3.6)

project(zmq_transport)

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
if(COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} does not support C++17.")
endif()

file(GLOB_RECURSE HEADERS "include/zmq/*.h")
file(GLOB_RECURSE SRC     "src/zmq/*.c*")

add_library(${PROJECT_NAME} ${SRC} ${HEADERS})

target_include_directories(zmq_transport PUBLIC ./include)

target_compile_definitions(zmq_transport PRIVATE ZMQ_TRANSPORT_LIBRARY zmq)
