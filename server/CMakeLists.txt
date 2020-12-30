cmake_minimum_required(VERSION 3.5)
project(code-snippet-app)

find_package(Qt5Core    REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Sql     REQUIRED)
find_package(Qt5Test    REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(src)
#add_subdirectory(lib/qhttpengine)
