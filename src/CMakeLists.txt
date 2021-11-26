set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(Gui)
list(APPEND components "Gui")

add_subdirectory(Domain)
list(APPEND components "Domain")

if(ENABLE_CLI_APPLICATION)
  add_subdirectory(CLI)
  list(APPEND components "CLI")
endif()

set_property(TARGET Gui PROPERTY FOLDER "src")
