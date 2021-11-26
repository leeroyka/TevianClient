project(CLI)

find_package(Qt5 ${QT_REQUIRED_VERSION} COMPONENTS Core REQUIRED)

file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME}
  ${HEADERS}
  ${SOURCES}
)

target_link_libraries (${PROJECT_NAME}
  PUBLIC
  Domain
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}
)
