project(Server)

set(ServerFiles
  Server.cpp Server.h
)

add_library(Server ${ServerFiles})

find_package(Qt5Widgets)
find_package(Qt5Network)

set_target_properties(Server PROPERTIES AUTOMOC TRUE)

target_link_libraries(Server Qt5::Widgets Qt5::Network)