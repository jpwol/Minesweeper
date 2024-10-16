cmake_minimum_required(VERSION 3.10)
project(Minesweeper VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRC_FILES "src/*.cpp")

add_executable(Minesweeper ${SRC_FILES})

target_include_directories(Minesweeper PRIVATE include)

target_link_libraries(Minesweeper
  PRIVATE
    SDL2main
    SDL2_image
    SDL2
)

set_target_properties(Minesweeper PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
