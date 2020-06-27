#################
#	GLFW
#################

IF(GLFW_ROOT)
find_package(glfw QUIET)
ENDIF()
IF(GLFW_FOUND)
	MESSAGE(NOTICE "We found GLFW!!!! dont use the submodule")

	add_library(zeno-glfw INTERFACE)
	target_include_directories(zeno-glfw INTERFACE ${GLFW_INCLUDE_DIRS})
	target_link_libraries(zeno-glfw INTERFACE ${GLFW_LIBRARIES})
ELSE(GLFW_FOUND)
	MESSAGE(NOTICE "We did not find GLFW, do use the submodule")

	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW without examples")
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW without tests")
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW without docs")
	add_subdirectory(glfw EXCLUDE_FROM_ALL)

	add_library(zeno-glfw INTERFACE)
	target_link_libraries(zeno-glfw INTERFACE glfw)
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

find_package(GLEW QUIET)
IF (GLEW_FOUND) 
	MESSAGE(NOTICE "We found GLEW!!!! dont use the submodule")
	MESSAGE(NOTICE "GLEW_LIBRARY: ${GLEW_LIBRARY}")
	MESSAGE(NOTICE "GLEW_INCLUDE_DIR: ${GLEW_INCLUDE_DIR}")

	add_library(zeno-glew INTERFACE)
	target_include_directories(zeno-glew INTERFACE ${GLEW_INCLUDE_DIR})
	target_link_libraries(zeno-glew INTERFACE ${GLEW_LIBRARY})
	IF (${GLEW_STATIC})
		target_compile_definitions(zeno-glew INTERFACE GLEW_STATIC=ON)
	ENDIF()
ELSE(GLEW_FOUND)
	MESSAGE(NOTICE "We did not find GLEW, do use the submodule")
	
	SET(glew-cmake_BUILD_SHARED OFF CACHE BOOL "Build the shared glew library")
	SET(glew-cmake_BUILD_STATIC ON CACHE BOOL "Build the static glew library")

	IF (${GLEW_STATIC}) 
		SET(glew-cmake_BUILD_SHARED ON)
		SET(glew-cmake_BUILD_STATIC OFF)
	ELSE(${GLEW_STATIC})
		SET(glew-cmake_BUILD_SHARED OFF)
		SET(glew-cmake_BUILD_STATIC ON)
	ENDIF()

	SET(ONLY_LIBS ON CACHE BOOL "Do not build executables")

	IF (${CMAKE_CXX_COMPILER_ID} STREQUAL ${MSVC})
		MESSAGE(TRACE "Visual Studio Compiler detected, need to 'make extensions' via the project upgrade")
		SET(MAKE_GLEW_PROJECT_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/../scripts/build_glew_extensions.ps1")
		execute_process(COMMAND powershell -ExecutionPolicy Bypass -File ${MAKE_GLEW_PROJECT_SCRIPT} OUTPUT VERBOSE)


	ENDIF()

	add_subdirectory(glew EXCLUDE_FROM_ALL)
	
	add_library(zeno-glew INTERFACE)
	target_link_libraries(zeno-glew INTERFACE glew)
	IF (${GLEW_STATIC})
		target_compile_definitions(zeno-glew INTERFACE GLEW_STATIC=ON)
	ENDIF()
ENDIF()

#################
#	OpenGl
#################
if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()
find_package(OpenGL REQUIRED)
add_library(zeno-opengl INTERFACE)
target_include_directories(zeno-opengl INTERFACE ${OPENGL_INCLUDE_DIRECTORIES})
target_link_libraries(zeno-opengl INTERFACE ${OPENGL_LIBRARIES})