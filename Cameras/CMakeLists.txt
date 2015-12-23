project(Cameras)

set(CamerasFiles
  Camera.cpp Camera.h
  Pinhole.cpp Pinhole.h
)

add_library(Cameras ${CamerasFiles})
