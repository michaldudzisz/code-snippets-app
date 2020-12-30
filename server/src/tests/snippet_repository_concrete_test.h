#ifndef SNIPPET_REPOSITORY_CONCRETE_TEST
#define SNIPPET_REPOSITORY_CONCRETE_TEST

#include <QtTest/QtTest>
#include "snippet_repository_concrete.h"

class SnippetRepositoryConcreteTest : public QObject
{
    Q_OBJECT

private:

    Snippet createExampleSnippet();

private slots:

    void saveSnippet();

};

#endif