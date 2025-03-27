cmake_minimum_required(VERSION 3.15)

project(SimpleMathLibrary C)
add_library(SimpleMathLibrary SHARED "generic.c" "vec2.c" "vec3.c" "")
target_link_libraries(SimpleMathLibrary m) # GCC math library
