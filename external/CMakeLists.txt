include(build_external_project.cmake)

message(STATUS "****** Managing external projects in:")
message(STATUS "CMAKE_CURRENT_LIST_DIR ~> ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_BINARY_DIR ~> ${CMAKE_BINARY_DIR}")


set(EXTERNAL_PROJECT_NAME "OpenCV")
set(EXTERNAL_PROJECT_FOLDER ${CMAKE_CURRENT_LIST_DIR}/${EXTERNAL_PROJECT_NAME})
# build_external_project_url(
#     ${EXTERNAL_PROJECT_NAME}
#     ${EXTERNAL_PROJECT_FOLDER}
#     https://github.com/opencv/opencv/archive/3.1.0.zip
#     ${build-folder}
#     "make -j4"
#     -DBUILD_EXAMPLES=OFF
#     -DBUILD_PERF_TESTS=OFF
#     -DBUILD_TESTS=OFF
#     -DBUILD_opencv_python2=OFF
#     -DWITH_CUDA=OFF
#     -DWITH_CUFFT=OFF
#     -DWITH_GTK=OFF
#     -DWITH_IPP=OFF
#     -DWITH_MATLAB=OFF
#     -DWITH_QT=ON
#     -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})

build_external_project_git(
    ${EXTERNAL_PROJECT_NAME}
    ${EXTERNAL_PROJECT_FOLDER}
    https://github.com/opencv/opencv.git
    3.2.0
    "make -j4"
    -DENABLE_PRECOMPILED_HEADERS=OFF
    -DBUILD_EXAMPLES=OFF
    -DBUILD_PERF_TESTS=OFF
    -DBUILD_TESTS=OFF
    -DBUILD_opencv_python2=OFF
    -DWITH_CUDA=OFF
    -DWITH_CUFFT=OFF
    -DWITH_GTK=OFF
    -DWITH_IPP=OFF
    -DWITH_MATLAB=OFF
    -DWITH_QT=ON
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})

set(${EXTERNAL_PROJECT_NAME}_BUILD_DIR ${CMAKE_BINARY_DIR}/external/${PROJ} PARENT_SCOPE)

set(EXTERNAL_PROJECT_NAME "Cinder")
set(EXTERNAL_PROJECT_FOLDER ${CMAKE_CURRENT_LIST_DIR}/${EXTERNAL_PROJECT_NAME})
build_external_project_url(
    ${EXTERNAL_PROJECT_NAME}
    ${EXTERNAL_PROJECT_FOLDER}
    https://github.com/cinder/Cinder/archive/master.zip
    "make -j4"
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
set(${EXTERNAL_PROJECT_NAME}_BUILD_DIR ${CMAKE_BINARY_DIR}/external/${PROJ} PARENT_SCOPE)
set(CINDER_DIR ${EXTERNAL_PROJECT_FOLDER})

set(CINDER_BLOCK_NAME "ImGui")
get_cinder_block(
    ${CINDER_BLOCK_NAME}
    ${CINDER_DIR}
    https://github.com/simongeilfus/Cinder-ImGui.git)

set(CINDER_BLOCK_NAME "Asio")
get_cinder_block(
    ${CINDER_BLOCK_NAME}
    ${CINDER_DIR}    
    https://github.com/BanTheRewind/Cinder-Asio.git)
    
