macro(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
  if(MSVC)
    get_filename_component(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
    set(PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/${PrecompiledBasename}.pch")
    set(Sources ${${SourcesVar}})

    set_source_files_properties(${PrecompiledSource}
                                PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_OUTPUTS "${PrecompiledBinary}")
    set_source_files_properties(${Sources}
                                PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_DEPENDS "${PrecompiledBinary}")  
    # Add precompiled header to SourcesVar
    list(APPEND ${SourcesVar} ${PrecompiledSource})
  endif(MSVC)
endmacro(ADD_MSVC_PRECOMPILED_HEADER)

# want to pass a list to macro? please quote it in " " brackets
macro(construct_msvc_filters_by_dir_scheme inpSources)
	foreach (sourceFile ${inpSources})
		get_filename_component(name ${sourceFile} DIRECTORY)
		string(REPLACE "${PROJECT_SOURCE_DIR}/" "" relative_path ${name})
		string(REPLACE "/" "\\" filter_path ${relative_path})
		source_group(${filter_path} FILES ${sourceFile})
	endforeach (sourceFile)
endmacro(construct_msvc_filters_by_dir_scheme)

macro(setup_precompiled_header precompiledHeader precompiledSource allSource)
	if(MSVC)
		GET_FILENAME_COMPONENT(headerBaseName ${precompiledHeader} NAME_WE)
		GET_FILENAME_COMPONENT(hName ${precompiledHeader} NAME)
		#GET_FILENAME_COMPONENT(sName ${precompiledSource} NAME)
		SET(PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/${headerBaseName}.pch")
		
		#TODO: can we use file name instead of full path name?
		SET_SOURCE_FILES_PROPERTIES(${allSource}
									PROPERTIES COMPILE_FLAGS "/Yu\"${precompiledHeader}\" /FI\"${precompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                    OBJECT_DEPENDS "${PrecompiledBinary}")  
		SET_SOURCE_FILES_PROPERTIES(${precompiledSource}
							PROPERTIES COMPILE_FLAGS "/Yc\"${hName}\" /Fp\"${PrecompiledBinary}\""
							OBJECT_OUTPUTS "${PrecompiledBinary}")
	endif(MSVC)
endmacro(setup_precompiled_header)