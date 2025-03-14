cmake_minimum_required(VERSION 3.15)

project(SimpleMath C)
subdirs("library" "test")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
include_directories(${CMAKE_SOURCE_DIR}/include)
