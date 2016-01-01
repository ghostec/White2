project(Lights)

set(LightsFiles
  Light.cpp Light.h
  Ambient.cpp Ambient.h
  PointLight.cpp PointLight.h
)

add_library(Lights ${LightsFiles})
