project(World)

set(WorldFiles
  World.cpp World.h
  ViewPlane.cpp ViewPlane.h
)

add_library(World ${WorldFiles})
