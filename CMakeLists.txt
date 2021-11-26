cmake_minimum_required(VERSION 2.8.12)

project(TevianClient CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

option(ENABLE_CLI_APPLICATION	"Console client application"	${DEFAULT_OPT})

add_subdirectory(src)
