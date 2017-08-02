
execute_process(COMMAND git submodule update --recursive --init -- Cinder-ImGui
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Cinder-ImGui
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-ImGui/src/CinderImGui.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-ImGui/lib/imgui/imgui.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-ImGui/lib/imgui/imgui_demo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-ImGui/lib/imgui/imgui_draw.cpp)
target_include_directories(Cinder-ImGui PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-ImGui/include
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-ImGui/lib/imgui)

target_link_libraries(Cinder-ImGui cinder)

execute_process(COMMAND git submodule update --recursive --init -- Cinder-Asio
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Cinder-Asio
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-Asio/src/ClientInterface.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-Asio/src/DispatcherInterface.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-Asio/src/ServerInterface.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-Asio/src/SessionInterface.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-Asio/src/TcpClient.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-Asio/src/TcpServer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-Asio/src/TcpSession.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-Asio/src/UdpClient.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-Asio/src/UdpServer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-Asio/src/UdpSession.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-Asio/src/WaitTimer.cpp)

target_include_directories(Cinder-Asio PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/Cinder-Asio/src/)

target_link_libraries(Cinder-Asio cinder)
