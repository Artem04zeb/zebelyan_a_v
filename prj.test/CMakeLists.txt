add_executable(rational_test rational_test.cpp)
target_link_libraries(rational_test rational doctest::doctest)
add_test(NAME rational_test COMMAND rational_test)

add_executable(matrixs.test matrixs.test.cpp)
target_link_libraries(matrixs.test matrixs doctest::doctest)
add_test(NAME matrixs.test COMMAND matrixs.test)
