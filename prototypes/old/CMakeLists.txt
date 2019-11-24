cmake_minimum_required(VERSION 2.8)

project(OpencvTest)

set(OpenCV_STATIC ON)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB INCLUDES "*.h")
file(GLOB SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${INCLUDES} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
