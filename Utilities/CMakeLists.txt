project(Utilities)

set(UtilitiesFiles
  Math.h
  Constants.h
  Normal.cpp Normal.h
  Point3D.cpp Point3D.h
  Point2D.cpp Point2D.h
  Ray.cpp Ray.h
  RGBColor.cpp RGBColor.h
  ShadeRec.cpp ShadeRec.h
  Vector3D.cpp Vector3D.h
  MessageQueue.cpp MessageQueue.h
  MessagePixel.cpp MessagePixel.h
)

add_library(Utilities ${UtilitiesFiles})
