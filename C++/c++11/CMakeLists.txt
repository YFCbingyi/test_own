cmake_minimum_required (VERSION 3.0) 

PROJECT(threads)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 ")

message("===" ${CMAKE_BINARY_DIR})
file( GLOB ALL_SOURCES ${CMAKE_BINARY_DIR}/../*.cpp ${CMAKE_BINARY_DIR}/../*.cxx)

foreach( testsourcefile ${ALL_SOURCES} )
    get_filename_component(fileName ${testsourcefile} NAME)
    string(REPLACE ".cpp" "" testname ${fileName} )
    string(REPLACE ".cxx" "" testname ${testname} )
    
    ADD_EXECUTABLE( ${testname} ${CMAKE_BINARY_DIR}/../${fileName} )
endforeach(testsourcefile ${ALL_SOURCES} )


#    This file will define the following variables:
#      - OpenCV_LIBS                 : The list of libraries to links against.
#      - OpenCV_LIB_DIR              : The directory where lib files are. Calling LINK_DIRECTORIES
#                                      with this path is NOT needed.
#      - OpenCV_INCLUDE_DIRS         : The OpenCV include directories.
#      - OpenCV_COMPUTE_CAPABILITIES : The version of compute capability
#      - OpenCV_VERSION              : The version of this OpenCV build. Example: "2.3.1"
#      - OpenCV_VERSION_MAJOR        : Major version part of OpenCV_VERSION. Example: "2"
#      - OpenCV_VERSION_MINOR        : Minor version part of OpenCV_VERSION. Example: "3"
#      - OpenCV_VERSION_PATCH        : Patch version part of OpenCV_VERSION. Example: "1"
#
#    Advanced variables:
#      - OpenCV_SHARED
#      - OpenCV_CONFIG_PATH
#      - OpenCV_INSTALL_PATH
#      - OpenCV_LIB_COMPONENTS
#      - OpenCV_EXTRA_COMPONENTS
#      - OpenCV_USE_MANGLED_PATHS
#      - OpenCV_HAVE_ANDROID_CAMERA
