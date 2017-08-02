
execute_process(COMMAND git submodule update --recursive --init -- Cinder
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
execute_process(COMMAND git submodule update --recursive --init -- OpenCV
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(ENABLE_PRECOMPILED_HEADERS OFF CACHE BOOL "OpenCV Option:")
set(BUILD_EXAMPLES OFF CACHE BOOL "OpenCV Option:")
set(BUILD_PERF_TESTS OFF CACHE BOOL "OpenCV Option:")
set(BUILD_TESTS OFF CACHE BOOL "OpenCV Option:")
set(BUILD_opencv_apps OFF CACHE BOOL "OpenCV Option:")
set(BUILD_opencv_python2 OFF CACHE BOOL "OpenCV Option:")
set(BUILD_opencv_world ON CACHE BOOL "OpenCV Option:")
set(WITH_CUDA OFF CACHE BOOL "OpenCV Option:")
set(WITH_CUFFT OFF CACHE BOOL "OpenCV Option:")
set(WITH_GTK OFF CACHE BOOL "OpenCV Option:")
set(WITH_IPP OFF CACHE BOOL "OpenCV Option:")
set(WITH_IPP_A OFF CACHE BOOL "OpenCV Option:")
set(WITH_MATLAB OFF CACHE BOOL "OpenCV Option:")
set(WITH_QT OFF CACHE BOOL "OpenCV Option:")
add_subdirectory(OpenCV)

set(CINDER_BOOST_USE_SYSTEM ON CACHE BOOL "Cinder Option:")
set(CINDER_VERBOSE ON CACHE BOOL "Cinder Verbose output")
add_subdirectory(Cinder)

add_subdirectory(Cinder-Blocks)
