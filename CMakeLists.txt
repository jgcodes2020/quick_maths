cmake_minimum_required(VERSION 3.15)
project(quick_maths
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(triangles
  src/triangles.cpp
  src/line_eq.cpp
)
target_include_directories(triangles
  PUBLIC include
)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)