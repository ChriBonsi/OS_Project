cmake_minimum_required(VERSION 3.27)
project(OS_Project C)

set(CMAKE_C_STANDARD 17)

add_executable(OS_Project main.c
        FileEncrypter.h
        SimpleEncrypter.c
)