# - Try to find OpenAL-Soft
# and define
#
#  OPENALSOFT_FOUND          - System has OpenAL-Soft
#  OPENALSOFT_INCLUDE_DIR    - The OpenAL-Soft include directories
#  OPENALSOFT_LIBRARY        - The OpenAL-Soft libraries

find_path(OPENALSOFT_INCLUDE_DIR 
  NAMES AL/al.h
  HINTS
    "${OPENALSOFT_ROOT}/include"
  PATHS
    /usr/include
    /usr/local/include
    /usr/target/include
    /sw/include
    /opt/local/include
)

find_library(OPENALSOFT_LIBRARY DOC "Absolute path to OpenAlSoft library." 
  NAMES libopenal openal libOpenAL32 OpenAL32 OpenAL32.dll soft_oal.dll
  HINTS
    "${OPENALSOFT_ROOT}/lib"
  PATHS
    /usr/local/lib
    /usr/lib
    /lib
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(OPENALSOFT DEFAULT_MSG OPENALSOFT_LIBRARY OPENALSOFT_INCLUDE_DIR)

mark_as_advanced(OPENALSOFT_INCLUDE_DIR OPENALSOFT_LIBRARY) 