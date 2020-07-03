cmake_minimum_required(VERSION 2.8)
project(hello-benchmark)

find_package(benchmark REQUIRED)

add_executable(benchmark functions.cpp main.cpp)
target_link_libraries(benchmark PRIVATE benchmark::benchmark_main)
