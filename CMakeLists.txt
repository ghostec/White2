cmake_minimum_required(VERSION 3.3)
project(White)

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

add_executable(White main.cpp)

set (CMAKE_PREFIX_PATH "C:\\Qt\\5.5\\qtbase\\lib\\cmake\\")
find_package(Qt5Widgets)

set(LIBRARIES Utilities Tracers GeometricObjects World Samplers Cameras BRDFs Lights Materials)
target_link_libraries(White ${LIBRARIES} Qt5::Widgets)

set_property(TARGET White ${LIBRARIES} PROPERTY CXX_STANDARD 11)
