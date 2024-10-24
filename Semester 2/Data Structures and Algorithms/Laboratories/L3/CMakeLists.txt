cmake_minimum_required(VERSION 3.28)
project(New_Folder_With_Items)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(New_Folder_With_Items
        ExtendedTest.cpp
        ListIterator.cpp
        main.cpp
        ShortTest.cpp
        SortedIndexedList.cpp)
