#include "snippet_repository_concrete_test.h"
#include <cstdio>
#include <QDebug>

void SnippetRepositoryConcreteTest::initTestCase()
{
    repository_ = SnippetRepositoryConcrete::getInstance();
}

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

    repository_->saveSnippet(snippet);
}

void SnippetRepositoryConcreteTest::pullSnippets()
{
    Snippet snippet = createExampleSnippet();

    QList<QVariant> snippets = repository_->pullSnippets();

    QJsonArray json_arr;

    for (auto snipp : snippets)
    {
        json_arr.append(snipp.value<Snippet>().toJson());
    }
}

void SnippetRepositoryConcreteTest::pullSnippetsByAuthorAndTitle()
{
    
    SnippetSearchPattern pattern;
    pattern.setLang("c++");
    QList<QVariant> snippets = repository_->pullSnippets(pattern);

    pattern.setAuthorSubsequence("rnam"); // use rnam e
    snippets = repository_->pullSnippets(pattern);

    pattern.setTitleSubsequence("some"); // some title
    snippets = repository_->pullSnippets(pattern);

    QJsonArray json_arr;

    for (auto snipp : snippets)
    {
        json_arr.append(snipp.value<Snippet>().toJson());
    }
}
