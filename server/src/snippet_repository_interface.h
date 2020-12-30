#ifndef SNIPPET_REPOSITORY_INTERFACE_H
#define SNIPPET_REPOSITORY_INTERFACE_H

#include <QVector>
#include <QString>
#include <QVariant>

#include "snippet.h"

class SnippetRepositoryInterface
{
public:
    virtual void saveSnippet(Snippet &s) = 0;
    virtual QVariant findSnippetsByTitle(QString &s) = 0;
};

#endif