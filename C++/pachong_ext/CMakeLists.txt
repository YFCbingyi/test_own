cmake_minimum_required (VERSION 3.0) 

PROJECT(pachong)

option(ALLOW_SEARCH "Set OFF to build pachong" OFF)

set (CMAKE_CXX_STANDARD 14)


message("===" ${CMAKE_BINARY_DIR})


INCLUDE_DIRECTORIES(
    include
    ../normal/
    )

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

set(SOURCE_FILE ${DIR_SRCS})
if(${ALLOW_SEARCH})
ADD_EXECUTABLE( ${PROJECT_NAME}
    ${SOURCE_FILE}
 )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DALLOW_SEARCH ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DALLOW_SEARCH ")
else()
ADD_EXECUTABLE( ${PROJECT_NAME}
    ${SOURCE_FILE}
 )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 ")
endif()
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
  curl
  htmlcxx
  )




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
