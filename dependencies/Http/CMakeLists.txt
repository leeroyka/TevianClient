project(Http LANGUAGES CXX)

cmake_minimum_required(VERSION 3.2.0)

set(CMAKE_CXX_STANDARD 11)
set(Ignore ${QT_QMAKE_EXECUTABLE})

# Является ли проект подпроектом
get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)
if(IS_SUBPROJECT)
  message(STATUS "-----Project has a parent scope.")
  set(DEFAULT_OPT OFF)
else()
  message(STATUS "-----Project doesn't have a parent scope.")
  set(DEFAULT_OPT ON)  
  set(VERSION_MAJOR 0)
  set(VERSION_MINOR 0)
endif()

if(NOT DEFINED VERSION_MAJOR OR NOT DEFINED VERSION_MINOR)
  message(FATAL_ERROR "VERSION_MAJOR or VERSION_MINOR is not set")
endif()

# Разбираем собранные файлы в классическую структуру
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_subdirectory(src)
