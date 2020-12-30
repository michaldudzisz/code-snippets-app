#include "snippet_repository_concrete_test.h"

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

    SnippetRepositoryConcrete &repository = SnippetRepositoryConcrete::getInstance();

    repository.saveSnippet(snippet);
}
