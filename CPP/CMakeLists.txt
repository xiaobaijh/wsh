cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Set the project name
project(Wsh)

file(GLOB SOURCES "src/*.cc")

include_directories(src)
# Add an executable
add_executable(Wsh ${SOURCES})