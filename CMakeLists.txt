cmake_minimum_required(VERSION 3.24)
project(sortowanie C)

set(CMAKE_C_STANDARD 11)

add_executable(sortowanie main.c src/io.c src/array.c src/utils.c src/benchmark.c src/insertion.c src/selection.c src/bubble.c src/quicksort.c src/benchmark.c src/shell.c src/heap.c)
