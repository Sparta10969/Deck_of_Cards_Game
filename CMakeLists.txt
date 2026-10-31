cmake_minimum_required(VERSION 3.16)

project(bdz1 CXX)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(--coverage -Wall -Wextra)
add_link_options(--coverage)

add_subdirectory(lib)
add_subdirectory(main)

enable_testing()
add_subdirectory(test)