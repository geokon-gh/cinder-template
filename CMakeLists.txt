
cmake_minimum_required(VERSION 3.0)
project(cinder-template)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Export compile commands for Rtags")

find_package(Git REQUIRED)
add_subdirectory(contrib)

add_executable(cinder-template 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp )
target_link_libraries(cinder-template 
  opencv_world 
  cinder 
  Cinder-ImGui 
  Cinder-Asio)
