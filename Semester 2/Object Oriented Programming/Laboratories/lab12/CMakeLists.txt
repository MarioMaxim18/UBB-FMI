cmake_minimum_required(VERSION 3.28)
project(lab12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/mario/Qt/6.7.0/macos")

find_package(Qt6 COMPONENTS
        Core
        Widgets
        REQUIRED)

add_executable(lab12 main.cpp
        mainwindow.cpp)

target_link_libraries(lab12
        Qt::Core
        Qt::Widgets
)

