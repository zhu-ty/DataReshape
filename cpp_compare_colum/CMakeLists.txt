# CMake entry point.
# Note that this CMakeLists.txt in fully independent from the one in the parent directory
# (since that's the goal of this tutorial !)

# For an introduction to CMake, see
# http://www.cmake.org/cmake/help/cmake_tutorial.html (at least steps 1 and 2)

cmake_minimum_required (VERSION 3.5)
set(name "Compare")
project ( ${name} )

# cmake module
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# c++ version
set (CMAKE_CXX_STANDARD 11)


set(MY_HEADER_FILES
)

set(MY_SOURCE_FILES 
	main.cpp
)
include_directories(
	${PROJECT_SOURCE_DIR}	
)

add_executable(${name}
	${MY_HEADER_FILES}
	${MY_SOURCE_FILES}
	main.cpp
	)

target_link_libraries(${name}
	)
