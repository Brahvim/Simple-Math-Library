cmake_minimum_required(VERSION 3.15)

project(SimpleMath C)
subdirs("library" "test")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} -O3 -march=native -ffast-math -funroll-loops -mavx2 -mprefer-vector-width=256\
    -funsafe-math-optimizations -ftree-vectorize -fopt-info-vec-optimized \
    -Wall -Wno-unknown-pragmas -Wno-missing-braces")
include_directories(${CMAKE_SOURCE_DIR}/include)
