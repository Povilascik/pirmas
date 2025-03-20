cmake_minimum_required(VERSION 3.29)
project(pirmas)

set(CMAKE_CXX_STANDARD 14)

add_executable(saugojimas_masyve
    saugojimas_masyve.cpp
    saugojimas_masyve.h)
add_executable(programa
    pirma_uzd.cpp
        duomenys.cpp
        duomenys.h
        )
# Set Release build type with optimizations
set(CMAKE_BUILD_TYPE Release)

# Add compiler-specific optimization flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
elseif(MSVC)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
endif()

set(TEST_FILE_LOCATION "${CMAKE_SOURCE_DIR}/")
target_compile_definitions(programa PRIVATE TEST_FILE_LOCATION="${TEST_FILE_LOCATION}")