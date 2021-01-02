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
    virtual QList<QVariant> pullSnippets(SnippetSearchPattern &pattern) = 0;
};

#endif