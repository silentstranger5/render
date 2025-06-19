cmake_minimum_required(VERSION 3.12)

project(array)

add_library(array array.c)

target_include_directories(array PUBLIC "${array_SOURCE_DIR}")
