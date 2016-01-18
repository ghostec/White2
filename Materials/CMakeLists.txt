project(Materials)

set(MaterialsFiles
  Material.cpp Material.h
  SolidColor.cpp SolidColor.h
  Matte.cpp Matte.h
  Phong.cpp Phong.h
)

add_library(Materials ${MaterialsFiles})

target_link_libraries(Materials BRDFs)
