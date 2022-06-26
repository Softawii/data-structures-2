cmake_minimum_required(VERSION 3.22)
project(ReplacementSelection C)

set(CMAKE_C_STANDARD 23)

add_executable(ReplacementSelection main.c src/core.h test/cliente.h)
