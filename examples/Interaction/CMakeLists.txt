SET(AppMain "ZenoInteraction")

ADD_EXECUTABLE(${AppMain} "main.cpp")
SET_PROPERTY(TARGET ${AppMain} PROPERTY CXX_STANDARD 17)
SET_PROPERTY(TARGET ${AppMain} PROPERTY CXX_STANDARD_REQUIRED ON)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE zeno-glew)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE zeno-opengl)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE zeno-glfw)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE zeno-interaction)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE zeno-game)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE zeno-graphics)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE zeno-window)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE zeno-core)

ADD_CUSTOM_COMMAND(TARGET ${AppMain} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:${AppMain}>/data)