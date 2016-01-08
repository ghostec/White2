project(Client)

set(ClientFiles
  Client.cpp Client.h
)

add_library(Client ${ClientFiles})

find_package(Qt5Widgets)
find_package(Qt5Network)

set_target_properties(Client PROPERTIES AUTOMOC TRUE)

target_link_libraries(Client Qt5::Widgets Qt5::Network)