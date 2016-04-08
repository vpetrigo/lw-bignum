macro(add_lw_big_test _TEST_NAME)
    add_executable(${_TEST_NAME}_tests
        ${_TEST_NAME}_tests.cpp)
    target_link_libraries(${_TEST_NAME}_tests
        ${GTEST_MAIN_LIBRARIES}
        ${LW_BIG_LIBRARIES})
    add_test(NAME lw_big_${_TEST_NAME}_tests COMMAND ${_TEST_NAME}_tests)
    # Group under the "tests" project folder in IDEs such as Visual Studio.
    set_property(TARGET ${_TEST_NAME}_tests PROPERTY FOLDER "tests")
endmacro()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LW_BIG_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS})
    
add_lw_big_test(bignum_converter)