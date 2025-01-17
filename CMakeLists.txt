cmake_minimum_required(VERSION 3.9)

# In case of linux, tell it to places binaries in bin folder
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Library locations (Change these to the appropriate path on your machine)
set(INCLUDE_DIR C:/DevelopmentLibraries/include/)
set(LIB_DIR C:/DevelopmentLibraries/lib/x64)

# Tell CMake where to look for include and libs
include_directories(${INCLUDE_DIR})
link_directories(${LIB_DIR})

# Create a project
project(BreakoutProject)

file(GLOB_RECURSE BREAKOUT_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
add_executable(Breakout ${BREAKOUT_SRCS})
target_link_libraries(Breakout SDL2)
if (EMSCRIPTEN)
set(CMAKE_EXECUTABLE_SUFFIX .html)
set(CMAKE_C_FLAGS "-s USE_SDL=2")
else()
target_link_libraries(Breakout SDL2main)
endif()