cmake_minimum_required(VERSION 3.12)

project(glm)

add_library(glm glm.c)

target_include_directories(glm PUBLIC "${glm_SOURCE_DIR}")
