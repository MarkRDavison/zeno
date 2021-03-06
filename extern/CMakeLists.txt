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
ELSE()
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
	add_subdirectory(Catch2 EXCLUDE_FROM_ALL)
ENDIF()

#################
#	FakeIt
#################
IF (${ZENO_BUILD_TESTS})
	add_subdirectory(FakeIt EXCLUDE_FROM_ALL)

	add_library(fakeit INTERFACE)
	target_include_directories(fakeit INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/FakeIt/single_header/catch")
ENDIF()

#################
#	stb
#################
add_library(zeno-stb INTERFACE)
target_include_directories(zeno-stb INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/stb")

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
ELSE()
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
#	Freetype2
#################
IF(FREETYPE_ROOT)
	SET(ENV{FREETYPE_DIR} ${FREETYPE_ROOT})
ENDIF()
FIND_PACKAGE(Freetype QUIET)
IF (FREETYPE_FOUND)
	add_library(zeno-freetype INTERFACE)
	target_include_directories(zeno-freetype INTERFACE ${FREETYPE_INCLUDE_DIRS})
	target_link_libraries(zeno-freetype INTERFACE ${FREETYPE_LIBRARY})
ELSE()
	set(CMAKE_DISABLE_FIND_PACKAGE_HarfBuzz TRUE CACHE BOOL "Disable the HarfBuzz library")
	set(CMAKE_DISABLE_FIND_PACKAGE_BrotliDec TRUE CACHE BOOL "Disable the BrotliDec library")

	add_subdirectory(freetype2 EXCLUDE_FROM_ALL)	
	add_library(zeno-freetype INTERFACE)
	target_link_libraries(zeno-freetype INTERFACE freetype)
ENDIF()

#################
#	OpenGl
#################
find_package(OpenGL REQUIRED)
add_library(zeno-opengl INTERFACE)
target_include_directories(zeno-opengl INTERFACE ${OPENGL_INCLUDE_DIRECTORIES})
target_link_libraries(zeno-opengl INTERFACE ${OPENGL_LIBRARIES})
if(UNIX AND NOT APPLE)
	target_link_libraries(zeno-opengl INTERFACE GL)
endif()

#################
#	OpenAl
#################
FIND_PACKAGE(OPENALSOFT QUIET)
IF (OPENALSOFT_FOUND)
	add_library(zeno-openal INTERFACE)
	target_include_directories(zeno-openal INTERFACE ${OPENALSOFT_INCLUDE_DIR})
	target_link_libraries(zeno-openal INTERFACE ${OPENALSOFT_LIBRARY})
ELSE()
	set(ALSOFT_UTILS OFF CACHE BOOL "Build utility programs")
	set(ALSOFT_NO_CONFIG_UTIL ON CACHE BOOL "Disable building the alsoft-config utility")
	set(ALSOFT_EXAMPLES OFF CACHE BOOL "Build example programs")

	add_subdirectory(OpenAL EXCLUDE_FROM_ALL)

	add_library(zeno-openal INTERFACE)
	target_link_libraries(zeno-openal INTERFACE OpenAL)
ENDIF()