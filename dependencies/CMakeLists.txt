set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
add_subdirectory(Http)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(json)
