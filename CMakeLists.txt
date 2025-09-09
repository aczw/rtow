cmake_minimum_required(VERSION 4.0..4.1)

project(rtow VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS NO)

add_compile_options(-Wall -Wextra -O2 -g)

set(SRC_DIR src)
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
add_executable(rtow ${SOURCES})
target_include_directories(rtow PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}")
