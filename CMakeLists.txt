cmake_minimum_required(VERSION 3.13)

project(
  aoc-2023
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

include(EflGetModules)
Efl_Getmodules(efl::config)
add_subdirectory(3rdparty)

add_library(aoc_utils INTERFACE)
target_link_libraries(aoc_utils INTERFACE aoc::3rdparty efl::config)
target_include_directories(aoc_utils INTERFACE utils)
add_library(aoc::utils ALIAS aoc_utils)

add_subdirectory(days)