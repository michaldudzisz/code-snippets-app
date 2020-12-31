include_directories("../")

set(TEST_HEADERS
    snippettest.h
    snippet_repository_concrete_test.h
)

set(TEST_SOURCES
    test.cpp
    snippettest.cpp
    snippet_repository_concrete_test.cpp
)

add_executable(test ${TEST_SOURCES} ${SOURCES_TO_TEST})

target_link_libraries(test 
    qhttpengine
    Qt5::Core 
    Qt5::Network 
    Qt5::Sql 
    Qt5::Test
)
