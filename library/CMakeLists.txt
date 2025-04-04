cmake_minimum_required(VERSION 3.15)

project(SimpleMathLibrary C)
add_library(
  SimpleMathLibrary SHARED
  "generic.c"
  "vec2.c"
  "vec3.c"
  "quat.c"
  "mat44.c"
  "mat33.c"
  "mat22.c")
target_link_libraries(SimpleMathLibrary m) # GCC math library (`math.h`!).
