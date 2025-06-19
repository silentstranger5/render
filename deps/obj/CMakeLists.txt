cmake_minimum_required(VERSION 3.12)

project(obj)

add_library(obj obj.c)

target_link_libraries(obj PRIVATE array)
target_include_directories(obj PUBLIC "${obj_SOURCE_DIR}")
