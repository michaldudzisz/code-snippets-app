TEMPLATE = app 
TARGET = main

QT = widgets core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += /usr/local/include/boost/boost_1_61_0/

//HEADERS += ./include/*.hpp
SOURCES += ./src/*.cpp

DESTDIR=target #Target file directory
OBJECTS_DIR=objects #Intermediate object files directory
MOC_DIR=generated_files #Intermediate moc files directory
