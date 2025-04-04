cmake_minimum_required(VERSION 3.15)

project(SimpleMathLibrary C)
add_library(
  SimpleMathLibrary SHARED
  "vec2.c"
  "vec3.c"
  "quat.c"
  "mat22.c"
  "mat33.c"
  "mat44.c"
  "generic.c")
target_link_libraries(SimpleMathLibrary m) # GCC math library (`math.h`!).
