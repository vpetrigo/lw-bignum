macro(set_cache_variable VAR_NAME VAR_DESCRIPTION)
    set(${VAR_NAME} ${${VAR_NAME}} CACHE INTERNAL ${VAR_DESCRIPTION})
    message(STATUS "Set ${VAR_NAME} to ${${VAR_NAME}}.")
endmacro()

if(${LW_BIG_TEST_ENABLE})
  add_subdirectory(googletest)
  set(GTEST_FOUND TRUE)
  set(GTEST_LIBRARIES gtest)
  set(GTEST_MAIN_LIBRARIES gtest_main)
  set(GTEST_BOTH_LIBRARIES gtest gtest_main)
  set(GTEST_INCLUDE_DIRS ${gtest_SOURCE_DIR}/include)

  # Group under the "tests/gtest" project folder in IDEs such as Visual Studio.
  set_property(TARGET gtest PROPERTY FOLDER "tests/gtest")
  set_property(TARGET gtest_main PROPERTY FOLDER "tests/gtest")

  set_cache_variable(GTEST_FOUND "Set if libgtest was found or built")
  set_cache_variable(GTEST_LIBRARIES "Location of libgtest")
  set_cache_variable(GTEST_MAIN_LIBRARIES "Location of libgtest-main")
  set_cache_variable(GTEST_BOTH_LIBRARIES "Location of both gtest libraries")
  set_cache_variable(GTEST_INCLUDE_DIRS "Location of gtest include files")
endif()
