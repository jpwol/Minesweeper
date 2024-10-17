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
  target_include_directories(Minesweeper 
    PRIVATE 
      include 
      C://SDL2/include
  )

  target_link_libraries(
    Minesweeper
      mingw32
      C://SDL2/lib/libSDL2main.a 
      C://SDL2/lib/libSDL2_image.a
      C://SDL2/lib/libSDL2.a
      winmm
      dinput8
      dxguid
      dxerr8
      ole32
      oleaut32
      imm32
      version
      setupapi
  )
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -mwindows")
elseif(UNIX)
  target_include_directories(Minesweeper PRIVATE include)
  target_link_libraries(SDL2main SDL2_image SDL2)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()
