cmake_minimum_required(VERSION 3.0)

add_subdirectory(googletest)
enable_testing()

set (_test_srcs
	test_BundleManager.cpp
)

add_executable(runTests ${_test_srcs})
target_link_libraries (runTests PRIVATE CMSCore gtest gmock gtest_main)
add_test (NAME BundleManagerTest, COMMAND runTests)


