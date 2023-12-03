add_library(aoc-3rdparty INTERFACE)
add_library(aoc::3rdparty ALIAS aoc-3rdparty)

set(ABSL_ENABLE_INSTALL ON)
set(ABSL_PROPAGATE_CXX_STD ON)

add_subdirectory(abseil-cpp)
add_subdirectory(fmt)
add_subdirectory(re2)

target_link_libraries(aoc-3rdparty INTERFACE 
  fmt::fmt re2::re2 absl::strings)