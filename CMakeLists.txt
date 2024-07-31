cmake_minimum_required(VERSION 3.30.1)
project(chippi8)

set(CMAKE_CXX_STANDARD 11)
set(EXTERNAL_LIB_HEADERS lib/imgui)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCES
    src/main.cpp
    src/chip8/base.cpp)

set(HEADERS
    src/chip8/base.h
    src/display/sdl.h
    src/display/imgui_sdl.h)

add_executable(chippi8 ${SOURCES})

target_link_libraries(chippi8 ${SDL2_LIBRARIES})