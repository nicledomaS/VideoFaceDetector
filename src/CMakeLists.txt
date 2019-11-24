cmake_minimum_required(VERSION 2.8)

file(GLOB INCLUDES "*.h")
file(GLOB SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${INCLUDES} ${SOURCES})
