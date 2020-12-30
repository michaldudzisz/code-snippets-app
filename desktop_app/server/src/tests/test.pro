INCLUDEPATH += ../../lib/include
INCLUDEPATH += ../
LIBS += -L../../lib/lib -lqhttpengine

QMAKE_RPATHDIR += ../../lib/lib

HEADERS += ../apihandler.h 
HEADERS += ../snippet.h 
HEADERS += ../too_long_content_exception.h 
HEADERS += ../unsupported_language_exception.h
HEADERS += ../invalid_snippet_json_exception.h

SOURCES += ../apihandler.cpp 
SOURCES += ../snippet.cpp 
SOURCES += ../too_long_content_exception.cpp
SOURCES += ../unsupported_language_exception.cpp
SOURCES += ../invalid_snippet_json_exception.cpp


HEADERS += snippettest.h

SOURCES += snippettest.cpp
SOURCES += test.cpp

QT -= gui
QT += core
QT += network
QT += testlib

TARGET = test
