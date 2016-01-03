cmake_minimum_required(VERSION 3.2)
project(White)

set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(./)

add_subdirectory(Utilities)
add_subdirectory(Tracers)
add_subdirectory(GeometricObjects)
add_subdirectory(World)
add_subdirectory(Samplers)
add_subdirectory(Cameras)
add_subdirectory(BRDFs)
add_subdirectory(Lights)
add_subdirectory(Materials)

set(LIBRARIES Utilities Tracers GeometricObjects Samplers Cameras BRDFs Lights Materials World)

FIND_PACKAGE(Threads REQUIRED)

if(GUI)
  add_executable(White main.cpp)

  set (CMAKE_PREFIX_PATH "C:\\Qt\\5.5\\qtbase\\lib\\cmake\\")
  find_package(Qt5Widgets)

  target_link_libraries(White ${LIBRARIES} Qt5::Widgets)
else(GUI)
  add_executable(White main_nogui.cpp)

  target_link_libraries(White ${LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
endif(GUI)

set_property(TARGET White ${LIBRARIES} PROPERTY CXX_STANDARD 11)
