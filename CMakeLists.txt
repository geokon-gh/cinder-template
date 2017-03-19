cmake_minimum_required(VERSION 3.0)
project(buubletea)
#set(CMAKE_CXX_COMPILER /usr/bin/g++-5)

find_package(Git REQUIRED)

    message(STATUS "!!! Build type")
    message(STATUS ${CMAKE_BUILD_TYPE})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(build-folder build-release)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(build-folder build-debug)
else()
    set(build-folder build-unknown)
endif()
    
add_subdirectory(external)

find_package(OpenCV PATHS ${OpenCV_BUILD_DIR} NO_DEFAULT_PATH REQUIRED)
find_package(JPEG REQUIRED)

add_subdirectory(src)

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/Cinder/src" ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE )
set( BLOCKS_DIR ${CINDER_PATH}/blocks)
include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

set( OLD_CINDER_BLOCKS_INCLUDES
	${BLOCKS_DIR}/ImGui/include
	${BLOCKS_DIR}/ImGui/lib/imgui
	${BLOCKS_DIR}/Asio/src)
	
set( INCLUDES_FILES
    ${OLD_CINDER_BLOCKS_INCLUDES}
    OpenCV_INCLUDE_DIRS)

set( OLD_CINDER_BLOCKS_SOURCES
	${BLOCKS_DIR}/ImGui/src/CinderImGui.cpp
	${BLOCKS_DIR}/ImGui/lib/imgui/imgui.cpp
	${BLOCKS_DIR}/ImGui/lib/imgui/imgui_demo.cpp
	${BLOCKS_DIR}/ImGui/lib/imgui/imgui_draw.cpp)
	
set( SOURCES_FILES
    ${OLD_CINDER_BLOCKS_SOURCES}
    ${APP_PATH}/src/cinderlights.cpp )
ci_make_app(
    APP_NAME    cinderlights
    INCLUDES    ${INCLUDES_FILES}
    SOURCES     ${SOURCES_FILES}
	CINDER_PATH ${CINDER_PATH}
#    BLOCKS      ImGui
    LIBRARIES   ${OpenCV_LIBS}
)

