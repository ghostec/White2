project(Network)

set(NetworkFiles
  Message.cpp Message.h
  Server.cpp Server.h
  Client.cpp Client.h
  Worker.cpp Worker.h
)

add_library(Network ${NetworkFiles})

find_package(Qt5Widgets)
find_package(Qt5Network)

set_target_properties(Network PROPERTIES AUTOMOC TRUE)

target_link_libraries(Network Utilities Qt5::Widgets Qt5::Network)