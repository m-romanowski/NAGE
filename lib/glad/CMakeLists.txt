cmake_minimum_required(VERSION 3.1.0)
project(Glad)

add_library(glad include/glad/glad.h include/glad/glad_glx.h src/glad_glx.c src/glad.c)
target_include_directories(glad PUBLIC include/)
