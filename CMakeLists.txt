cmake_minimum_required(VERSION 3.8)

project(su)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(warnings "/WX" "/W4")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(warnings "-Wall" "-Wextra" "-Wpedantic" "-Werror")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(warnings "-Wall" "-Weverything" "-pedantic" "-Werror")
endif()

add_compile_options(${warnings})

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

subdirs(su)
subdirs(tests)
