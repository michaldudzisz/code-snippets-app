INCLUDEPATH += ../lib/include
LIBS += -L../lib/lib -lqhttpengine

QMAKE_RPATHDIR += ../lib/lib

HEADERS += apihandler.h
HEADERS += snippet.h
HEADERS += snippet_repository_interface.h
HEADERS += snippet_repository_concrete.h
HEADERS += too_long_content_exception.h
HEADERS += unsupported_language_exception.h
HEADERS += invalid_snippet_json_exception.h

SOURCES += apihandler.cpp 
SOURCES += main.cpp 
SOURCES += snippet.cpp 
SOURCES += snippet_repository_concrete.cpp
SOURCES += too_long_content_exception.cpp
SOURCES += unsupported_language_exception.cpp
SOURCES += invalid_snippet_json_exception.cpp

TEMPLATE += subdirs
SUBDIRS += tests/



QT -= gui
QT += core
QT += network
QT += sql
QT += testlib

TARGET = server
