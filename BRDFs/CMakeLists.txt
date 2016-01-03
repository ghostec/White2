project(BRDFs)

set(BRDFsFiles
  BRDF.cpp BRDF.h
  Lambertian.cpp Lambertian.h
  GlossySpecular.cpp GlossySpecular.h
)

add_library(BRDFs ${BRDFsFiles})
