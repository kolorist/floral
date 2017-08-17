cmake_minimum_required (VERSION 3.0)

# utils
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake")
include(utils)

project (floral_unit_test C CXX)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/../include")

add_subdirectory("${PROJECT_SOURCE_DIR}/.." "floral")

#preprocessor defines
add_definitions(-D_MSC_VER=1900)

file(GLOB_RECURSE file_list
	"${PROJECT_SOURCE_DIR}/include/*.h"
	"${PROJECT_SOURCE_DIR}/include/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(floral_unit_test ${file_list})

#construct_msvc_filters_by_dir_scheme("${file_list}")

target_link_libraries(floral_unit_test floral)
