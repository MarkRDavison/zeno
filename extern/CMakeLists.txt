if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()
if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

#################
#	GLFW
#################
IF(GLFW_ROOT)
find_package(GLFW QUIET)
ENDIF()
IF(GLFW_FOUND)
	add_library(zeno-glfw INTERFACE)
	target_include_directories(zeno-glfw INTERFACE ${GLFW_INCLUDE_DIRS})
	target_link_libraries(zeno-glfw INTERFACE ${GLFW_LIBRARIES})

ELSE(GLFW_FOUND)
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
	add_library(zeno-glew INTERFACE)
	target_include_directories(zeno-glew INTERFACE ${GLEW_INCLUDE_DIR})
	target_link_libraries(zeno-glew INTERFACE ${GLEW_LIBRARY})
	IF (${GLEW_STATIC})
		target_compile_definitions(zeno-glew INTERFACE GLEW_STATIC=ON)
	ENDIF()
ELSE(GLEW_FOUND)
	SET(ONLY_LIBS ON CACHE BOOL "Do not build executables")
	SET(glew-cmake_BUILD_STATIC ON CACHE BOOL "Build the static glew library")
	SET(glew-cmake_BUILD_SHARED OFF CACHE BOOL "Build the shared glew library")

	IF (GLEW_STATIC) 
		SET(glew-cmake_BUILD_SHARED OFF)
		SET(glew-cmake_BUILD_STATIC ON)
	ELSE()
		SET(glew-cmake_BUILD_SHARED ON)
		SET(glew-cmake_BUILD_STATIC OFF)
	ENDIF()
	
	add_subdirectory(glew EXCLUDE_FROM_ALL)
	
	add_library(zeno-glew INTERFACE)
	target_include_directories(zeno-glew INTERFACE ${GLEW_INCLUDE_DIR})
	IF (GLEW_STATIC)
		target_link_libraries(zeno-glew INTERFACE libglew_static)
	ELSE()
		target_link_libraries(zeno-glew INTERFACE libglew_shared)
	ENDIF()
ENDIF()

#################
#	OpenGl
#################
find_package(OpenGL REQUIRED)
add_library(zeno-opengl INTERFACE)
target_include_directories(zeno-opengl INTERFACE ${OPENGL_INCLUDE_DIRECTORIES})
MESSAGE(STATUS ${OPENGL_LIBRARIES})
target_link_libraries(zeno-opengl INTERFACE ${OPENGL_LIBRARIES})
if(UNIX AND NOT APPLE)
	TARGET_LINK_LIBRARIES(zeno-opengl INTERFACE GL)
endif()