cmake_minimum_required(VERSION 3.16)

project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(GameOfLife
    main.cpp
    GameBoard.cpp
    GameBoard.h
    Bacteria.cpp
    Bacteria.h
)

if(MSVC)
    target_compile_options(GameOfLife PRIVATE /W4)
else()
    target_compile_options(GameOfLife PRIVATE -Wall -Wextra -Wpedantic)
endif()
