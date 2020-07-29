cmake_minimum_required (VERSION 3.0) 

PROJECT(jpegenc)

# Requires libjpeg
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	find_package( jpeg REQUIRED )
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	list(APPEND app_required_libs m jpeg)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 ")


include_directories(${JPEG_INCLUDE_DIR})

ADD_EXECUTABLE( jpegenc jpegenc.c test_jpeg.c )
TARGET_LINK_LIBRARIES( jpegenc ${JPEG_LIBRARY} ${app_required_libs})
