cmake_minimum_required(VERSION 3.30.1)
project(chippi8)

set(CMAKE_CXX_STANDARD 11)
set(EXTERNAL_LIB_HEADERS lib/imgui)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(chippi8 src/main.cpp)
target_link_libraries(chippi8 ${SDL2_LIBRARIES})
target_include_directories(chippi8 PRIVATE ${EXTERNAL_LIB_HEADERS})