cmake_minimum_required(VERSION 3.15)

# find_package(GLEW REQUIRED) find_package(glfw3 REQUIRED)
project(CMakeTemplateTest C)
add_executable(CMakeTemplateTest "main.c")
target_link_libraries(
  CMakeTemplateTest PRIVATE CMakeTemplateLibrary
  # OpenGL::GL /usr/lib/x86_64-linux-gnu/libglfw.so
  # /usr/lib/x86_64-linux-gnu/libGLEW.so
)
