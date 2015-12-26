project(Cameras)

set(CamerasFiles
  Camera.cpp Camera.h
  Pinhole.cpp Pinhole.h
)

add_library(Cameras ${CamerasFiles})

set (CMAKE_PREFIX_PATH "C:\\Qt\\5.5\\msvc2012\\")
find_package(Qt5Widgets)

target_link_libraries(Cameras Qt5::Widgets)
