add_subdirectory(Catch2)

if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()
find_package(OpenGL REQUIRED)


# TODO: Need to check if GLFW_ROOT is set, if so try and use the existing libraries we are pointed to
#	Either way try the find_package, if its just installed it'd be nice to not compile etc.
#	Maybe remove the submodule init etc if we find it without it
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW without examples")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW without tests")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW without docs")
add_subdirectory(glfw EXCLUDE_FROM_ALL)

SET(glew-cmake_BUILD_SHARED OFF CACHE BOOL "Build the shared glew library")
SET(glew-cmake_BUILD_STATIC ON CACHE BOOL "Build the static glew library")
SET(ONLY_LIBS ON CACHE BOOL "Do not build executables")
add_subdirectory(glew EXCLUDE_FROM_ALL)

