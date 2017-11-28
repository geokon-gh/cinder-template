cmake_minimum_required(VERSION 3.0)

# HUNTER dependencency manager
include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.19.167.tar.gz"
    SHA1 "244a13718ea2e6c0c8998d15559c7e459f615708"
    LOCAL
    )


project(cinder-template)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Export compile commands for Rtags")

hunter_add_package(Cinder)
find_package(Cinder)
add_executable(cinder-template 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp )
target_link_libraries(cinder-template 
  Cinder::cinder)

