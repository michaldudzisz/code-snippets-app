#ifndef SNIPPET_REPOSITORY_INTERFACE_H
#define SNIPPET_REPOSITORY_INTERFACE_H

#include <QVector>
#include <QString>
#include <QVariant>
#include <QList>

#include "snippet.h"
#include "snippet_search_pattern.h"

class SnippetRepositoryInterface
{
public:
    virtual void saveSnippet(Snippet &s) = 0;
    virtual QList<QVariant> pullSnippets() = 0;
    virtual QList<QVariant> findSnippetsByFields(const SnippetSearchPattern &pattern) = 0;
    virtual QList<QVariant> findSnippetsByTitle(const QString &title) = 0;
    virtual QList<QVariant> findSnippetsByLanguage(const QString &lang) = 0;
};

#endif