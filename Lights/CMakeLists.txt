project(Lights)

set(LightsFiles
  Light.cpp Light.h
  Ambient.cpp Ambient.h
  AmbientOccluder.cpp AmbientOccluder.h
  PointLight.cpp PointLight.h
)

add_library(Lights ${LightsFiles})
