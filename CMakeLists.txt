cmake_minimum_required(VERSION 3.0)
project(buubletea)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Export compile commands for Rtags")

find_package(Git REQUIRED)

add_subdirectory(contrib)
add_subdirectory(src)

#set( INCLUDES_FILES
#  OpenCV_INCLUDE_DIRS)

set( SOURCES_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GaussianWave.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp )

add_executable(cinderlights ${SOURCES_FILES})
target_link_libraries(cinderlights opencv_world cinder Cinder-ImGui Cinder-Asio)
