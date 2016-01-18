project(Tracers)

set(TracersFiles
  RayCast.cpp RayCast.h
  Tracer.cpp Tracer.h
)

add_library(Tracers ${TracersFiles})

target_link_libraries(Tracers Utilities)
