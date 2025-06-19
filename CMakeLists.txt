cmake_minimum_required(VERSION 3.12)

project(render)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(deps/glm)
add_subdirectory(deps/obj)
add_subdirectory(deps/array)
add_subdirectory(deps/SDL3-3.2.14 EXCLUDE_FROM_ALL)
add_subdirectory(deps/SDL3_image-3.2.4 EXCLUDE_FROM_ALL)

add_library(graphics STATIC graphics.c)
add_executable(render main.c)

target_include_directories(render PRIVATE "${render_SOURCE_DIR}")

target_link_libraries(graphics PRIVATE glm obj array
    SDL3::SDL3 SDL3_image::SDL3_image)

target_link_libraries(render PRIVATE 
    glm obj array graphics
    SDL3::SDL3 SDL3_image::SDL3_image)
