add_subdirectory(Catch2)

SET(ONLY_LIBS ON CACHE BOOL "Do not build executables")
add_subdirectory(glew EXCLUDE_FROM_ALL)

FIND_PACKAGE(GLEW REQUIRED)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW without examples")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW without tests")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW without docs")
add_subdirectory(glfw EXCLUDE_FROM_ALL)

FIND_PACKAGE(GLFW REQUIRED)