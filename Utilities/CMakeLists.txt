project(Utilities)

set(UtilitiesFiles
  Normal.cpp Normal.h
  Point3D.cpp Point3D.h
  Ray.cpp Ray.h
  RGBColor.cpp RGBColor.h
  ShadeRec.cpp ShadeRec.h
  Vector3D.cpp Vector3D.h
)

add_library(Utilities ${UtilitiesFiles})
