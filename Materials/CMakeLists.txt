project(Materials)

set(MaterialsFiles
  Material.cpp Material.h
  Matte.cpp Matte.h
)

add_library(Materials ${MaterialsFiles})
