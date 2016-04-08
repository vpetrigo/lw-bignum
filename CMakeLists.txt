cmake_minimum_required(VERSION 3.2)

project(lw_big)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if(MINGW)
  set(gtest_disable_pthreads ON CACHE BOOL "Disable pthreads on MinGW")
endif()
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LW_BIG_LIBRARIES lw_big CACHE INTERNAL "")
set(LW_BIG_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include CACHE INTERNAL "")

option(LW_BIG_TEST_ENABLE "Enable building of tests" ON)

add_subdirectory(deps)
add_subdirectory(src)
if(${LW_BIG_TEST_ENABLE})
  enable_testing()
  add_subdirectory(test)
endif()
