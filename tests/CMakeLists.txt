cmake_minimum_required (VERSION 3.0)

project (floral_unit_test C CXX)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory("${PROJECT_SOURCE_DIR}/.." "floral")

#preprocessor defines
add_definitions(
	-D_MSC_VER=1900
	-DFLORAL_UNIT_TEST)

target_compile_definitions(floral PUBLIC
	-DFLORAL_UNIT_TEST)

file(GLOB_RECURSE file_list
    "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(floral_unit_test ${file_list})

target_link_libraries(floral_unit_test floral)
