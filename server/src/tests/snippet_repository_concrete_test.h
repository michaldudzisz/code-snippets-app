#ifndef SNIPPET_REPOSITORY_CONCRETE_TEST
#define SNIPPET_REPOSITORY_CONCRETE_TEST

#include <QtTest/QtTest>
#include "snippet_repository_concrete.h"

class SnippetRepositoryConcreteTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void saveSnippet();
    void pullSnippets();
    void pullSnippetsByAuthorAndTitle();

private:
    Snippet createExampleSnippet();

    QSharedPointer<SnippetRepositoryInterface> repository_;
};

#endif