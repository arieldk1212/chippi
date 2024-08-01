cmake_minimum_required(VERSION 3.30.1)
project(chippi8)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)

set(IMGUI_LIBRARIES lib/imgui)
set(IMGUI_BACKENDS lib/imgui/backends)

set(SOURCES
    src/main.cpp
    src/chip8/base.cpp
    ${IMGUI_LIBRARIES}/imgui.cpp
    ${IMGUI_LIBRARIES}/imgui_demo.cpp
    ${IMGUI_LIBRARIES}/imgui_draw.cpp
    ${IMGUI_LIBRARIES}/imgui_tables.cpp
    ${IMGUI_LIBRARIES}/imgui_widgets.cpp
    ${IMGUI_BACKENDS}/imgui_impl_sdl2.cpp
    ${IMGUI_BACKENDS}/imgui_impl_opengl2.cpp
)

include_directories(${SDL2_INCLUDE_DIRS} ${IMGUI_LIBRARIES} ${IMGUI_BACKENDS})

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_LIBRARIES} ${SDL2_LIBRARIES} ${IMGUI_BACKENDS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})