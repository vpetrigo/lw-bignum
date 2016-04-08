cmake_minimum_required(VERSION 3.2)

project(lw_big)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LW_BIG_LIBRARIES lw_big CACHE INTERNAL "")
set(LW_BIG_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include CACHE INTERNAL "")

enable_testing()

add_subdirectory(deps)
add_subdirectory(src)
add_subdirectory(test)