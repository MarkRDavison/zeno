#################
#	GLFW
#################
find_package(glfw QUIET)
IF(GLFW_FOUND)
	MESSAGE(STATUS "We found GLFW!!!! dont use the submodule")
	MESSAGE(STATUS ${GLFW_INCLUDE_DIRS})
	MESSAGE(STATUS ${GLFW_LIBRARIES})
	add_library(glfw INTERFACE)
	target_include_directories(glfw INTERFACE ${GLFW_INCLUDE_DIRS})
	target_link_libraries(glfw INTERFACE ${GLFW_LIBRARIES})
ELSE(GLFW_FOUND)
	MESSAGE(STATUS "We did not find GLFW, do use the submodule")
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW without examples")
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW without tests")
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW without docs")
	add_subdirectory(glfw EXCLUDE_FROM_ALL)
ENDIF()

#################
#	Catch2
#################

IF (${ZENO_BUILD_TESTS})
	add_subdirectory(Catch2)
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