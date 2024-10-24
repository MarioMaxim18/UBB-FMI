cmake_minimum_required(VERSION 3.27)
project(sem2c C)

set(CMAKE_C_STANDARD 11)

add_executable(sem2c main.c
        da.h
        da.c)
