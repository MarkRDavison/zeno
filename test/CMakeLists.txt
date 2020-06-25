SET(TestMain "ZenoTest")

ADD_EXECUTABLE(${TestMain} "main.cpp")
TARGET_COMPILE_FEATURES(${TestMain} PRIVATE cxx_std_17)
TARGET_LINK_LIBRARIES(${TestMain} PRIVATE Catch2)

# Core Module Tests
ADD_SUBDIRECTORY("core")
TARGET_LINK_LIBRARIES(${TestMain} PRIVATE "zeno-core${LIBRARY_EXTENSION}")
ADD_SUBDIRECTORY("graphics")
TARGET_LINK_LIBRARIES(${TestMain} PRIVATE "zeno-graphics${LIBRARY_EXTENSION}")

include(CTest)
include("${PROJECT_SOURCE_DIR}/extern/Catch2/contrib/ParseAndAddCatchTests.cmake")
ParseAndAddCatchTests(${TestMain})