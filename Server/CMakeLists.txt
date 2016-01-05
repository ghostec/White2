project(Server)

set(ServerFiles
  WhiteServer.cpp WhiteServer.h
)

add_library(Server ${ServerFiles})

set(CMAKE_PREFIX_PATH "C:\\Qt\\5.5\\qtbase\\lib\\cmake\\")
find_package(Qt5Network)

set_target_properties(Server PROPERTIES AUTOMOC TRUE)

target_link_libraries(Server Qt5::Network)