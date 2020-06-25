add_subdirectory(Catch2)
find_package(OpenGL REQUIRED)



#FIND_PACKAGE(GLEW REQUIRED)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW without examples")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW without tests")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW without docs")
add_subdirectory(glfw EXCLUDE_FROM_ALL)

SET(glew-cmake_BUILD_SHARED OFF CACHE BOOL "Build the shared glew library")
SET(glew-cmake_BUILD_STATIC ON CACHE BOOL "Build the static glew library")
SET(ONLY_LIBS ON CACHE BOOL "Do not build executables")
add_subdirectory(glew EXCLUDE_FROM_ALL)

