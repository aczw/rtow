cmake_minimum_required(VERSION 4.0)

project(rtow VERSION 1.0.0 LANGUAGES CXX)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(MATERIAL_DIR "${SRC_DIR}/material")

add_executable(rtow
  ${SRC_DIR}/camera.cpp
  ${SRC_DIR}/color.cpp
  ${SRC_DIR}/hittable_list.cpp
  ${SRC_DIR}/intersection.cpp
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/ray.cpp
  ${SRC_DIR}/sphere.cpp
  ${SRC_DIR}/utils.cpp
  ${SRC_DIR}/vec3.cpp

  ${SRC_DIR}/ihittable.hpp
  ${SRC_DIR}/interval.hpp

  ${MATERIAL_DIR}/base_material.cpp
  ${MATERIAL_DIR}/dielectric_material.cpp
  ${MATERIAL_DIR}/lambertian_material.cpp
  ${MATERIAL_DIR}/metal_material.cpp
)

target_compile_features(rtow PRIVATE cxx_std_23)
target_compile_options(rtow PRIVATE -Wall -Wextra -Werror -Wpedantic -Wconversion -O2 -g)
set_target_properties(rtow PROPERTIES cxx_extensions OFF cxx_standard_required ON)
