cmake_minimum_required(VERSION 3.27)
project(program2spring24)

set(CMAKE_CXX_STANDARD 17)

add_executable(program2spring24 prog2test.cpp MyGraph.cpp test2_1.txt)
configure_file(test2_1.txt test2_1.txt)

