macro(AOC_CompileDay folder)
  add_executable(day-${folder} ${folder}/Driver.cpp)
  target_link_libraries(day-${folder} aoc::utils)
endmacro()