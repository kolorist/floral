cmake_minimum_required (VERSION 3.0)

project (floral)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB_RECURSE file_list
	"${PROJECT_SOURCE_DIR}/src/cu/*.cpp")

add_library(floral ${file_list})

#construct_msvc_filters_by_dir_scheme("${file_list}")
#setup_precompiled_header("${PROJECT_SOURCE_DIR}/include/stdafx.h"
#						 "${PROJECT_SOURCE_DIR}/src/stdafx.cpp"
#						 "${file_list}")