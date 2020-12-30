#include "snippettest.h"
#include "snippet_repository_concrete_test.h"

//QTEST_MAIN(SnippetTest)

int main(int argc, char *argv[])
{
    QCoreApplication test(argc, argv);

    int status = 0;
    auto run_test = [&status, argc, argv](QObject *obj) {
        status |= QTest::qExec(obj, argc, argv);
    };

    run_test(new SnippetTest);
    run_test(new SnippetRepositoryConcreteTest);
    
    return status;
}
