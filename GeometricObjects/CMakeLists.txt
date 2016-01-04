project(GeometricObjects)

set(GeometricObjectsFiles
  GeometricObject.cpp GeometricObject.h
  Primitives/Sphere.cpp Primitives/Sphere.h
  Primitives/Plane.cpp Primitives/Plane.h
)

add_library(GeometricObjects ${GeometricObjectsFiles})
