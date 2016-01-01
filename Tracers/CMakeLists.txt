project(Tracers)

set(TracersFiles
  RayCast.cpp RayCast.h
  MultipleObjects.cpp MultipleObjects.h
  Tracer.cpp Tracer.h
)

add_library(Tracers ${TracersFiles})

target_link_libraries(Tracers Utilities)
