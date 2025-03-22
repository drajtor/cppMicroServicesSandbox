cmake_minimum_required(VERSION 3.0)
project(CMSSandbox)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS ON)

find_package(CppMicroServices NO_MODULE REQUIRED)

add_subdirectory(dictionaryService)

set (_srcs 
	main.cpp
	BundleManager.cpp
	ConsoleLogger.cpp
)

add_executable(CMSSandbox ${_srcs})

target_link_libraries (CMSSandbox PRIVATE CppMicroServices dictionary_service)

