cmake_minimum_required(VERSION 3.0)
project(CMSSandbox)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CppMicroServices NO_MODULE REQUIRED)


set (_srcs 
	main.cpp
)

add_executable(CMSSandbox ${_srcs})

target_link_libraries (CMSSandbox PRIVATE CppMicroServices)

