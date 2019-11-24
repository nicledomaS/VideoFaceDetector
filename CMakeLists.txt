cmake_minimum_required(VERSION 2.8)

project(VideoFaceDetector)

option(WITH_PROTOTYPES "Turn on build prototypes" OFF)

add_subdirectory(src)

if(WITH_PROTOTYPES)
	add_subdirectory(prototypes)
endif()

