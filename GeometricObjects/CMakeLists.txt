project(GeometricObjects)

set(GeometricObjectsFiles
  GeometricObject.cpp GeometricObject.h
  Primitives/Sphere.cpp Primitives/Sphere.h
)

add_library(GeometricObjects ${GeometricObjectsFiles})
