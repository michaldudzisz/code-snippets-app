#include "snippet_repository_concrete_test.h"
#include <cstdio>
#include <QDebug>

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

    QSharedPointer<SnippetRepositoryConcrete> repository =
        SnippetRepositoryConcrete::getInstance();

    repository->saveSnippet(snippet);
}

void SnippetRepositoryConcreteTest::pullSnippets()
{
    Snippet snippet = createExampleSnippet();

    QSharedPointer<SnippetRepositoryInterface> repository =
        SnippetRepositoryConcrete::getInstance();

    QList<QVariant> snippets = repository->pullSnippets();

    QJsonArray json_arr;

    for (auto snipp : snippets)
    {
        json_arr.append(snipp.value<Snippet>().toJson());
    }

    QJsonDocument doc(json_arr);

    QString to_print(doc.toJson(QJsonDocument::Compact));
    //qDebug() << to_print;
}

void SnippetRepositoryConcreteTest::findSnippetsByFields()
{
    QSharedPointer<SnippetRepositoryInterface> repository =
        SnippetRepositoryConcrete::getInstance();
    
    SnippetSearchPattern pattern;
    pattern.setLang("c++");
    QList<QVariant> snippets = repository->findSnippetsByFields(pattern);

    pattern.setAuthorSubsequence("rnam"); // use rnam e
    snippets = repository->findSnippetsByFields(pattern);

    pattern.setTitleSubsequence("some"); // some title
    snippets = repository->findSnippetsByFields(pattern);

    QJsonArray json_arr;

    for (auto snipp : snippets)
    {
        json_arr.append(snipp.value<Snippet>().toJson());
    }

    QJsonDocument doc(json_arr);

    QString to_print(doc.toJson(QJsonDocument::Compact));
    qDebug() << to_print;
}
