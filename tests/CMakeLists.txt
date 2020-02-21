cmake_minimum_required (VERSION 3.0)

project (floral_test)

include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(".." "${PROJECT_BINARY_DIR}/floral")

#preprocessor defines
add_definitions(
	-DPLATFORM_WINDOWS
	-D_CRT_SECURE_NO_WARNINGS)

file(GLOB_RECURSE file_list
	"${PROJECT_SOURCE_DIR}/src/multithread_ring_buffer_test.cpp"

    "${PROJECT_SOURCE_DIR}/src/main.cpp")

add_executable(floral_test ${file_list})

target_link_libraries(floral_test floral)
