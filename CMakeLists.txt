cmake_minimum_required(VERSION 3.29)
project(pirmas)

set(CMAKE_CXX_STANDARD 14)

add_executable(saugojimas_masyve
    saugojimas_masyve.cpp
    saugojimas_masyve.h)
add_executable(pirmas
    pirma_uzd.cpp
        libr.h
        duomenys.h
        duomenys.cpp)
