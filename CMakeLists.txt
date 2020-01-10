cmake_minimum_required (VERSION 3.0)

project (floral C CXX)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")

if (${ANDROID_BUILD})
else()
endif (${ANDROID_BUILD})

if (${MSVC_PROJECT})
	file (GLOB_RECURSE file_list
		LIST_DIRECTORIES false
		"${PROJECT_SOURCE_DIR}/include/*.h"
		"${PROJECT_SOURCE_DIR}/include/*.inl"
		"${PROJECT_SOURCE_DIR}/src/*.cpp")
	# excluding unity build :(
	file (GLOB_RECURSE unity_build_list
		LIST_DIRECTORIES false
		"${PROJECT_SOURCE_DIR}/src/cu/*.cpp")
	list (REMOVE_ITEM file_list ${unity_build_list})
else ()
	file (GLOB_RECURSE file_list
		"${PROJECT_SOURCE_DIR}/src/cu/*.cpp")
endif (${MSVC_PROJECT})
	
add_definitions (
	-D_CRT_SECURE_NO_WARNINGS)

if (${ANDROID_BUILD})
	message(STATUS "floral will be built using Android configs")
	add_definitions (
		-DPLATFORM_POSIX)
		
	# platform abi
	if (${ANDROID_ABI} STREQUAL "arm64-v8a")
		message(STATUS "floral Android ABI: arm64")
		add_definitions (
			-DPOSIX64)
	else ()
		message(STATUS "floral Android ABI: arm")
		add_definitions (
			-DPOSIX32)
	endif (${ANDROID_ABI} STREQUAL "arm64-v8a")	
	
else ()
	message(STATUS "floral will be built using Windows configs")
	add_definitions (
		-DPLATFORM_WINDOWS)
	if (${MSVC_PROJECT})
		list (REMOVE_ITEM file_list
			"${PROJECT_SOURCE_DIR}/include/floral/thread/posix_thread.h"
			"${PROJECT_SOURCE_DIR}/include/floral/thread/posix_mutex.h"
			"${PROJECT_SOURCE_DIR}/include/floral/thread/posix_condition_variable.h"
			"${PROJECT_SOURCE_DIR}/src/thread/posix_thread.cpp"
			"${PROJECT_SOURCE_DIR}/src/thread/posix_mutex.cpp"
			"${PROJECT_SOURCE_DIR}/src/thread/posix_condition_variable.cpp"
			"${PROJECT_SOURCE_DIR}/src/io/nativeio_posix.cpp")
	endif (${MSVC_PROJECT})
endif (${ANDROID_BUILD})


add_library(floral ${file_list})

target_include_directories (floral PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

if (${MSVC_PROJECT})
	# organize filters
	foreach(_source IN ITEMS ${file_list})
		get_filename_component(_source_path "${_source}" PATH)
		file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
		string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
		source_group("${_group_path}" FILES "${_source}")
	endforeach()
endif (${MSVC_PROJECT})