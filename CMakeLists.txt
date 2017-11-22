cmake_minimum_required(VERSION 3.0)

# HUNTER dependencency manager
include("cmake/HunterGate.cmake")
HunterGate(
  URL "https://github.com/ruslo/hunter/archive/v0.18.58.tar.gz"
  SHA1 "3b39effc5ee1af4ef7487eabb1b0a7a7e10a7b3e"
  LOCAL
)


project(cinder-template)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Export compile commands for Rtags")

find_package(Git REQUIRED)

#hunter_add_package(Boost COMPONENTS regex chrono date_time filesystem system thread)
#find_package(Boost CONFIG REQUIRED)

hunter_add_package(OpenCV)
find_package(OpenCV CONFIG REQUIRED)

hunter_add_package(Cinder)

add_executable(cinder-template 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp )
target_link_libraries(cinder-template 
  OpenCV::opencv_world
  Cinder::cinder)

#  Cinder-ImGui 
#  Cinder-Asio)
