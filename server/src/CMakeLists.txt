include_directories("../lib/include")

set(HEADERS
    apihandler.h
    snippet.h
    snippet_repository_concrete.h
    too_long_content_exception.h
    unsupported_language_exception.h
    invalid_snippet_json_exception.h
    query_not_performed_exception.h
    repository_not_initialized_exception.h
    snippet_search_pattern.h
)

set(SOURCES
    main.cpp
    apihandler.cpp
    snippet.cpp
    snippet_repository_concrete.cpp
    too_long_content_exception.cpp
    unsupported_language_exception.cpp
    invalid_snippet_json_exception.cpp
    query_not_performed_exception.cpp
    repository_not_initialized_exception.cpp
    snippet_search_pattern.cpp
)

set(SOURCES_TO_TEST 
    ${CMAKE_CURRENT_LIST_DIR}/apihandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/snippet.cpp
    ${CMAKE_CURRENT_LIST_DIR}/snippet_repository_concrete.cpp
    ${CMAKE_CURRENT_LIST_DIR}/too_long_content_exception.cpp
    ${CMAKE_CURRENT_LIST_DIR}/unsupported_language_exception.cpp
    ${CMAKE_CURRENT_LIST_DIR}/invalid_snippet_json_exception.cpp
    ${CMAKE_CURRENT_LIST_DIR}/query_not_performed_exception.cpp
    ${CMAKE_CURRENT_LIST_DIR}/repository_not_initialized_exception.cpp
    ${CMAKE_CURRENT_LIST_DIR}/snippet_search_pattern.cpp
)

get_filename_component(ABSOLUTE_SERVER_PATH ${CMAKE_SOURCE_DIR} ABSOLUTE)

set(CMAKE_INSTALL_RPATH ${ABSOLUTE_SERVER_PATH}/lib/lib)

add_executable(server ${SOURCES})

add_library(qhttpengine SHARED IMPORTED)
set_property(TARGET qhttpengine PROPERTY IMPORTED_LOCATION
    ${CMAKE_INSTALL_RPATH}/libqhttpengine.so)

target_link_libraries(server 
    qhttpengine
    Qt5::Core 
    Qt5::Network 
    Qt5::Sql 
    Qt5::Test
)

add_subdirectory(tests)

