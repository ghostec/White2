project(Samplers)

set(SamplersFiles
  Sampler.cpp Sampler.h
  Jittered.cpp Jittered.h
  MultiJittered.cpp MultiJittered.h
  Regular.cpp Regular.h
)

add_library(Samplers ${SamplersFiles})

target_link_libraries(Samplers Utilities)
