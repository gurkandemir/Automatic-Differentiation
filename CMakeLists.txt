cmake_minimum_required(VERSION 2.8)
project(project4_gurkan_demir_2015400177_master)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    function.cpp
    function.h
    graph.cpp
    graph.h
    main.cpp
    variable.cpp
    variable.h)

add_executable(project4 ${SOURCE_FILES})