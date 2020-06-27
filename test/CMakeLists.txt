SET(TestMain "ZenoTest")

#TODO: Maybe have seperate executables per module?

ADD_EXECUTABLE(${TestMain} "main.cpp")
TARGET_LINK_LIBRARIES(${TestMain} PRIVATE Catch2)
SET_PROPERTY(TARGET ${TestMain} PROPERTY CXX_STANDARD 17)
SET_PROPERTY(TARGET ${TestMain} PROPERTY CXX_STANDARD_REQUIRED ON)

ADD_SUBDIRECTORY("core")
TARGET_LINK_LIBRARIES(${TestMain} PRIVATE "zeno-core${LIBRARY_EXTENSION}")
ADD_SUBDIRECTORY("graphics")
TARGET_LINK_LIBRARIES(${TestMain} PRIVATE "zeno-graphics${LIBRARY_EXTENSION}")

include(CTest)
include("${PROJECT_SOURCE_DIR}/extern/Catch2/contrib/ParseAndAddCatchTests.cmake")
ParseAndAddCatchTests(${TestMain})