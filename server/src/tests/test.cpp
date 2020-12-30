#include "snippettest.h"
#include "snippet_repository_concrete_test.h"

//QTEST_MAIN(SnippetTest)

int main(int argc, char *argv[])
{/*
    QCoreApplication app(argc, argv); 
    app.setAttribute(Qt::AA_Use96Dpi, true); 
    
    QTEST_SET_MAIN_SOURCE_PATH*/

    int status = 0;
    auto runTest = [&status, argc, argv](QObject *obj) {
        status |= QTest::qExec(obj, argc, argv);
    };

    runTest(new SnippetTest);
    runTest(new SnippetRepositoryConcreteTest);
    
    return status;
}
