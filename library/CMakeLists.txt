cmake_minimum_required(VERSION 3.15)

# find_package(OpenGL REQUIRED)
project(CMakeTemplateLibrary C)
add_library(CMakeTemplateLibrary SHARED "library.c")
target_link_libraries(
  CMakeTemplateLibrary m # GCC math library
  # OpenGL::GL /usr/lib/x86_64-linux-gnu/libGLEW.so
  # /usr/lib/x86_64-linux-gnu/libglfw3.so
)
