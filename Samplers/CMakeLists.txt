project(Samplers)

set(SamplersFiles
  Sampler.cpp Sampler.h
  Jittered.cpp Jittered.h
)

add_library(Samplers ${SamplersFiles})

target_link_libraries(Samplers Utilities)
