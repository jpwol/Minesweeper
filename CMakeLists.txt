cmake_minimum_required(VERSION 3.10)
project(Sand VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRC_FILES "src/*.cpp")

add_executable(Sand ${SRC_FILES})

include_directories(
  SYSTEM 
    C:/msys64/ucrt64/include
    C:/SDL2/include
)

target_include_directories(Sand PRIVATE include)

target_link_libraries(Sand
  PRIVATE
    C:/SDL2/lib/x64/SDL2main.lib
    C:/SDL2/lib/x64/SDL2.lib
)

set_target_properties(Sand PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
