project(Worker)

set(WorkerFiles
  Worker.cpp Worker.h
)

add_library(Worker ${WorkerFiles})

find_package(Qt5Widgets)
find_package(Qt5Network)

set_target_properties(Worker PROPERTIES AUTOMOC TRUE)

target_link_libraries(Worker Network World Qt5::Widgets Qt5::Network)
