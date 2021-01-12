cmake_minimum_required(VERSION 3.5)

project(desktop_app LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS
    Widgets
    Network
    Core
    REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS
    Widgets
    Network
    Core
    REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/presenter/mainwindow.cpp
        src/presenter/mainwindow.h
        src/view/mainwindow.ui
        src/presenter/addsnippetwindow.cpp
        src/presenter/addsnippetwindow.h
        src/view/addsnippetwindow.ui
        src/communication/worker.cpp
        src/communication/worker.h
        src/model/snippet.h
        src/model/snippet.cpp
        src/model/too_long_content_exception.h
        src/model/too_long_content_exception.cpp
        src/model/invalid_snippet_json_exception.h
        src/model/invalid_snippet_json_exception.cpp
        src/model/unsupported_language_exception.h
        src/model/unsupported_language_exception.cpp

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(desktop_app
        ${PROJECT_SOURCES}
    )
else()
  add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    )
