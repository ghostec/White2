cmake_minimum_required(VERSION 2.8)

if(${target} STREQUAL "gui")
  include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeGUI.txt)
elseif(target STREQUAL "server")
  include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeServer.txt)
  elseif(target STREQUAL "client")
  include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeClient.txt)
endif()