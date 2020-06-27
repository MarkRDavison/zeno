# CMake build : library

#configure variables
SET(MODULE_NAME "window")
SET(LIB_NAME "zeno-${MODULE_NAME}${LIBRARY_EXTENSION}")
#	set_target_properties(libglew_static PROPERTIES
#		OUTPUT_NAME "glew"
#		DEBUG_POSTFIX d)
# TODO: Insteadd of lib extensions


#configure directories
set (LIBRARY_MODULE_PATH "${PROJECT_SOURCE_DIR}/lib/${MODULE_NAME}")
set (LIBRARY_SRC_PATH "${LIBRARY_MODULE_PATH}/src" )
set (LIBRARY_INCLUDE_PATH "${LIBRARY_MODULE_PATH}/include")

#set sources
file (GLOB_RECURSE LIB_HEADER_FILES "${LIBRARY_INCLUDE_PATH}/*.hpp")
file (GLOB_RECURSE LIB_SOURCE_FILES "${LIBRARY_SRC_PATH}/*.cpp")


#set library
add_library (${LIB_NAME} ${LIB_SOURCE_FILES} ${LIB_HEADER_FILES})
target_link_libraries(${LIB_NAME} PRIVATE zeno-glfw)
target_link_libraries(${LIB_NAME} PRIVATE zeno-glew)
target_link_libraries(${LIB_NAME} PRIVATE zeno-opengl)
target_include_directories(${LIB_NAME} PUBLIC ${LIBRARY_INCLUDE_PATH})
target_include_directories(${LIB_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/lib/core/include")

add_library("zeno-${MODULE_NAME}" INTERFACE)
target_include_directories("zeno-${MODULE_NAME}" INTERFACE ${LIBRARY_INCLUDE_PATH})
target_link_libraries("zeno-${MODULE_NAME}" INTERFACE ${LIB_NAME})

#export vars
INSTALL(TARGETS ${LIB_NAME} DESTINATION ${LIBRARY_INSTALL_FOLDER})

IF (${BUILD_SHARED_LIBS})
INSTALL(FILES $<TARGET_PDB_FILE:${LIB_NAME}> DESTINATION ${LIBRARY_INSTALL_FOLDER} OPTIONAL)
ENDIF()


INSTALL(FILES ${LIB_HEADER_FILES} DESTINATION "include/zeno/${MODULE_NAME}")
INSTALL(FILES "${LIBRARY_INCLUDE_PATH}/zeno/${MODULE_NAME}.hpp" DESTINATION "include/zeno")