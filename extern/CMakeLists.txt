#################
#	Catch2
#################
add_subdirectory(Catch2)

#################
#	GLFW
#################
find_package(glfw QUIET)
IF(NOT GLFW_FOUND)
	MESSAGE(STATUS "We found GLFW!!!! dont use the submodule")
	add_library(glfw INTERFACE)
	target_include_directories(glfw INTERFACE ${GLFW_INCLUDE_DIRS})
	target_link_libraries(glfw INTERFACE ${GLFW_LIBRARIES})
ELSE(NOT GLFW_FOUND)
	MESSAGE(STATUS "We did not find GLFW, do use the submodule")
	find_package(Git REQUIRED)
	execute_process(COMMAND ${GIT_EXECUTABLE} submodule init extern/glfw WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} RESULT_VARIABLE _result1)# OUTPUT_QUIET ERROR_QUIET)
	execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive --remote extern/glfw WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} RESULT_VARIABLE _result2)# OUTPUT_QUIET ERROR_QUIET)
	if(${_result1} GREATER 0 OR ${_result2} GREATER 0)
		message(FATAL_ERROR "GLFW was not found.\n"
							"We tried: 'git submodule init && git submodule update' and resulted in error" )
	endif()
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW without examples")
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW without tests")
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW without docs")
	add_subdirectory(glfw EXCLUDE_FROM_ALL)
ENDIF()

#################
#	GLEW
#################
find_package(GLEW REQUIRED)
add_library(glew INTERFACE)
target_include_directories(glew INTERFACE ${GLEW_INCLUDE_DIR})
target_link_libraries(glew INTERFACE ${GLEW_LIBRARY})
IF (${GLEW_STATIC})
	target_compile_definitions(glew INTERFACE GLEW_STATIC=ON)
ENDIF()

#################
#	OpenGl
#################
if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()
find_package(OpenGL REQUIRED)
add_library(opengl INTERFACE)
target_include_directories(opengl INTERFACE ${OPENGL_INCLUDE_DIRECTORIES})
target_link_libraries(opengl INTERFACE ${OPENGL_LIBRARIES})