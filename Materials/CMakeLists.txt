project(Materials)

set(MaterialsFiles
  Material.cpp Material.h
  Matte.cpp Matte.h
  Phong.cpp Phong.h
)

add_library(Materials ${MaterialsFiles})

target_link_libraries(Materials BRDFs)
