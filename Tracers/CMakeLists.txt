project(Tracers)

set(TracersFiles
  MultipleObjects.cpp MultipleObjects.h
  Tracer.cpp Tracer.h
)

add_library(Tracers ${TracersFiles})

target_link_libraries(Tracers Utilities)
