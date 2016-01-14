project(World)

set(WorldFiles
  World.cpp World.h
  ViewPlane.cpp ViewPlane.h
  Renderer.cpp Renderer.h
  Settings.cpp Settings.h
)

add_library(World ${WorldFiles})

target_link_libraries(World Tracers GeometricObjects Samplers Lights Materials)
