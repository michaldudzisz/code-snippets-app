#ifndef SNIPPET_REPOSITORY_CONCRETE_TEST
#define SNIPPET_REPOSITORY_CONCRETE_TEST

#include <QtTest/QtTest>
#include "snippet_repository_concrete.h"

class SnippetRepositoryConcreteTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void initTestCase_data();
    void saveSnippet();
    void pullSnippetsNoArg();
    void pullSnippetsByAuthorAndTitle();

private:
    Snippet createExampleSnippet();

    QSharedPointer<SnippetRepositoryInterface> repository_;
    QDateTime itnitTestTime_;
};

#endif