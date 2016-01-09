project(Network)

if(target STREQUAL "server")
  add_subdirectory(Server)
  set(ENTITY Server)
elseif(target STREQUAL "client")
  add_subdirectory(Client)
  set(ENTITY Client)
elseif(target STREQUAL "worker")
  add_subdirectory(Worker)
  set(ENTITY Worker)
endif()

set(NetworkFiles
  Message.cpp Message.h
)

add_library(Network ${NetworkFiles})

find_package(Qt5Widgets)
find_package(Qt5Network)

set_target_properties(Network PROPERTIES AUTOMOC TRUE)

target_link_libraries(Network ${ENTITY} Utilities Qt5::Widgets Qt5::Network)