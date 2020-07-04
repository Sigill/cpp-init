cmake_minimum_required(VERSION 2.8)
project(hello-gtest)

include(CTest)

find_package(GTest REQUIRED
	# Uncomment when using a custom install of GoogleTest, otherwise
	# the FindGTest.cmake module provided by CMake will take precedence.
	# NO_MODULE
	)

add_executable(unit-tests test.cpp)
target_link_libraries(unit-tests PRIVATE GTest::gmock_main)
add_test(unit-tests unit-tests)
