cmake_minimum_required(VERSION 3.10)
project(CMSSandbox)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS ON)

find_package(CppMicroServices NO_MODULE REQUIRED)

add_subdirectory(dictionaryService)

set (_srcs 
	BundleManager.cpp
	ConsoleLogger.cpp
)

add_library (CMSCore ${_srcs})
target_link_libraries (CMSCore PUBLIC CppMicroServices dictionary_service)

add_executable(CMSSandbox main.cpp)
target_link_libraries (CMSSandbox PRIVATE CMSCore)



# --- Unit tests

option(BUILD_TESTS "Build tests" ON)

if (BUILD_TESTS)
	add_subdirectory(googletest)
	enable_testing()

	set (_test_srcs
		test_BundleManager.cpp
	)

	add_executable(runTests ${_test_srcs})
	target_link_libraries (runTests PRIVATE CMSCore gtest gmock gtest_main)
	add_test (NAME BundleManagerTest, COMMAND runTests)

endif()
