project(Cameras)

set(CamerasFiles
  Camera.cpp Camera.h
  CameraWorker.cpp CameraWorker.h
  Pinhole.cpp Pinhole.h
)

add_library(Cameras ${CamerasFiles})

if(GUI)
  find_package(Qt5Widgets)
endif(GUI)

if(GUI)
  target_link_libraries(Cameras Qt5::Widgets)
else(GUI)
  target_link_libraries(Cameras)
endif(GUI)