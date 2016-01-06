project(Client)

set(ClientFiles
  WhiteClient.cpp WhiteClient.h
)

add_library(Client ${ClientFiles})

find_package(Qt5Network)

set_target_properties(Client PROPERTIES AUTOMOC TRUE)

target_link_libraries(Client Qt5::Network)