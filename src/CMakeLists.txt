set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(Gui)
add_subdirectory(Domain)

set_property(TARGET Gui PROPERTY FOLDER "src")
