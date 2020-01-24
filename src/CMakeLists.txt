cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(OpenCV_STATIC ON)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB INCLUDES "*.h")
file(GLOB SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${INCLUDES} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${Boost_LIBRARIES})
