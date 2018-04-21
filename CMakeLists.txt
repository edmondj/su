cmake_minimum_required(VERSION 3.8)

project(su)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(warnings "/WX" "/W4")
  set(encoding "/utf-8")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(warnings "-Wall" "-Wextra" "-Wpedantic" "-Werror")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(warnings "-Wall" "-Wextra" "-Wpedantic" "-Werror")
endif()

add_compile_options(${warnings} ${encoding})

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

subdirs(su)
subdirs(tests)
