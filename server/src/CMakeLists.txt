
include_directories("../lib/include")

set(HEADERS
    apihandler.h
    snippet.h
    snippet_repository_concrete.h
    too_long_content_exception.h
    unsupported_language_exception.h
    invalid_snippet_json_exception.h
)

set(SOURCES
    main.cpp
    apihandler.cpp
    snippet.cpp
    snippet_repository_concrete.cpp
    too_long_content_exception.cpp
    unsupported_language_exception.cpp
    invalid_snippet_json_exception.cpp
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_filename_component(SRC_PATH ${CMAKE_SOURCE_DIR} ABSOLUTE)

message(${SRC_PATH})

#set(CMAKE_INSTALL_RPATH "${SRC_PATH}/lib/lib")

set(CMAKE_INSTALL_RPATH ${SRC_PATH}/lib/lib)

message(${CMAKE_INSTALL_RPATH})

add_executable(server ${SOURCES})

add_library(qhttpengine SHARED IMPORTED)
set_property(TARGET qhttpengine PROPERTY IMPORTED_LOCATION
    ${CMAKE_INSTALL_RPATH}/libqhttpengine.so)

target_link_libraries(server 
    qhttpengine
    #${CMAKE_INSTALL_RPATH}/qhttpengine
    Qt5::Core 
    Qt5::Network 
    Qt5::Sql 
    Qt5::Test
)























#cmake_minimum_required(VERSION 3.5)
#
#project(code-snippet-app-srever LANGUAGES CXX)
#
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#include_directories("../lib/include")
#
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
#find_package(Qt5Core    REQUIRED)
#find_package(Qt5Network REQUIRED)
#find_package(Qt5Sql     REQUIRED)
#find_package(Qt5Test    REQUIRED)
#
#set(PROJECT_SOURCES
#        main.cpp
#        apihandler.cpp
#        snippet.cpp
#        snippet_repository_concrete.cpp
#        too_long_content_exception.cpp
#        unsupported_language_exception.cpp
#        invalid_snippet_json_exception.cpp
#)
#
#
#add_executable(server
#        ${PROJECT_SOURCES}
#)
#
#
#target_link_libraries(server ${PROJECT_SOURCES}/../lib/lib
#        Qt5::Core Qt5::Network Qt5::Sql Qt5::Test
#)



#target_include_directories(server ${CMAKE_CURRENT_SOURCE_DIR})



#qt5_use_modules(server Core Network Sql Testlib)










#INCLUDEPATH += ../lib/include
#LIBS += -L../lib/lib -lqhttpengine

#QMAKE_RPATHDIR += ../lib/lib

#HEADERS += apihandler.h
#HEADERS += snippet.h
#HEADERS += snippet_repository_interface.h
#HEADERS += snippet_repository_concrete.h
#HEADERS += too_long_content_exception.h
#HEADERS += unsupported_language_exception.h
#HEADERS += invalid_snippet_json_exception.h

#SOURCES += apihandler.cpp 
#SOURCES += main.cpp 
#SOURCES += snippet.cpp 
#SOURCES += snippet_repository_concrete.cpp
#SOURCES += too_long_content_exception.cpp
#SOURCES += unsupported_language_exception.cpp
#SOURCES += invalid_snippet_json_exception.cpp

#TEMPLATE += subdirs
#SUBDIRS += tests/



#QT -= gui
#QT += core
#QT += network
#QT += sql
#QT += testlib

#TARGET = server
