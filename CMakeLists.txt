cmake_minimum_required(VERSION 3.8)
project(PACMAN)

set(CMAKE_C_STANDARD 99)
set(SOURCE src/graphics.c src/physics.c src/game.c main.c)
add_executable(PACMAN ${SOURCE})
include_directories(src /usr/include/SDL2)
target_link_libraries(PACMAN m SDL2 SDL2_gfx)
add_definitions(-D_REENTRANT)