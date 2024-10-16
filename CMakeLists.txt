cmake_minimum_required(VERSION 3.10)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRC_FILES "src/*.cpp")

set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")
file(MAKE_DIRECTORY ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

add_executable(Minesweeper ${SRC_FILES})

if(WIN32)
  set(LIBS C://SDL2/lib/x64/SDL2main.lib C://SDL2/lib/x64/SDL2_image.dll
           C://SDL2/lib/x64/SDL2.lib)
  set(SDL_INCLUDE C://SDL2/include)
elseif(UNIX)
  set(LIBS SDL2main SDL2_image SDL2)
endif()

if(WIN32)
  target_include_directories(Minesweeper PRIVATE include ${SDL_INCLUDE})
elseif(UNIX)
  target_include_directories(Minesweeper PRIVATE include)
endif()

target_link_libraries(Minesweeper ${LIBS})
