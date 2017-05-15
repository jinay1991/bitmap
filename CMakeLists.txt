cmake_minimum_required(VERSION 2.8)

project(BITMAP)

file(GLOB SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(bitmap STATIC ${SOURCE})
install(TARGETS bitmap DESTINATION lib)
