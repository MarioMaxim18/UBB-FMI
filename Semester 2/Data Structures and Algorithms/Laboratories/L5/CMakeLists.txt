cmake_minimum_required(VERSION 3.28)
project(lab5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab5
        App.cpp
        ExtendedTest.cpp
        ShortTest.cpp
        SMMIterator.cpp
        SortedMultiMap.cpp)
