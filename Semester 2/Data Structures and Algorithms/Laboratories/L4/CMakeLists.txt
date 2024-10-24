cmake_minimum_required(VERSION 3.28)
project(lab4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(New_Folder_With_Items
        App.cpp
        ExtendedTest.cpp
        Set.cpp
        SetIterator.cpp
        ShortTest.cpp)
