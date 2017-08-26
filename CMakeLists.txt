cmake_minimum_required (VERSION 3.0)

project (floral C CXX)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB_RECURSE file_list
	"${PROJECT_SOURCE_DIR}/src/cu/*.cpp")

add_library(floral ${file_list})

target_include_directories (floral PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
