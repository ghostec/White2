cmake_minimum_required(VERSION 3.3)
project(White)

include_directories(./)

add_subdirectory(Utilities)
add_subdirectory(Tracers)
add_subdirectory(GeometricObjects)
add_subdirectory(World)
add_subdirectory(Samplers)

add_executable(White main.cpp)

set(LIBRARIES White Utilities Tracers GeometricObjects World Samplers)

target_link_libraries(${LIBRARIES})

set_property(TARGET ${LIBRARIES} PROPERTY CXX_STANDARD 11)
