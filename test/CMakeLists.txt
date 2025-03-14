cmake_minimum_required(VERSION 3.15)

project(SimpleMathTest C)
add_executable(SimpleMathTest "main.c")
target_link_libraries(SimpleMathTest PRIVATE SimpleMathLibrary)
