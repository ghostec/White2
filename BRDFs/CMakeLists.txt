project(BRDFs)

set(BRDFsFiles
  BRDF.cpp BRDF.h
  Lambertian.cpp Lambertian.h
)

add_library(BRDFs ${BRDFsFiles})
