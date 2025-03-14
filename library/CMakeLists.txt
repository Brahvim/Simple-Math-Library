cmake_minimum_required(VERSION 3.15)

project(SimpleMathLibrary C)
add_library(SimpleMathLibrary SHARED "library.c")
target_link_libraries(SimpleMathLibrary m) # GCC math library
