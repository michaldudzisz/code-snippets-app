#include "snippet_repository_concrete_test.h"
#include <cstdio>

Snippet SnippetRepositoryConcreteTest::createExampleSnippet()
{
    Snippet s;
    s.setAuthor("username");
    s.setTitle("some title");
    s.setCreated(QDateTime::currentDateTime());
    s.setLang("c++");
    s.setContent("void main() {}");

    return s;
}

void SnippetRepositoryConcreteTest::saveSnippet()
{
    Snippet snippet = createExampleSnippet();

    QSharedPointer<SnippetRepositoryConcrete> repository
     = SnippetRepositoryConcrete::getInstance();

    if (repository.isNull())
        puts("jestem nulem");
    repository -> saveSnippet(snippet);

}
