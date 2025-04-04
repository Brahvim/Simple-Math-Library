cmake_minimum_required(VERSION 3.15)

project(SimpleMath C)
subdirs("library" "test")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} \
    -O3 \
    -Wall \
    -mavx2 \
    -msse4.2 \
    -ffast-math \
    -march=native \
    -funroll-loops \
    -ftree-vectorize \
    -Wno-missing-braces \
    -Wno-unknown-pragmas\
    -fopt-info-vec-optimized \
    -mprefer-vector-width=128 \
    -mprefer-vector-width=256 \
    -funsafe-math-optimizations")
include_directories(${CMAKE_SOURCE_DIR}/include)
