cmake_minimum_required(VERSION 2.8)
project(hello-boost-program-options)

find_package(Boost REQUIRED COMPONENTS system program_options)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Boost::system Boost::program_options)
