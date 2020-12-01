cmake_minimum_required(VERSION 3.1.0)
project(desktop_app)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output)
set (LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})


add_subdirectory(src)
add_subdirectory(tests)
enable_testing()

add_test(NAME MyTest COMMAND Test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)



