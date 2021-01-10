#ifndef SNIPPET_REPOSITORY_INTERFACE_H
#define SNIPPET_REPOSITORY_INTERFACE_H

#include <QVector>
#include <QString>
#include <QVariant>
#include <QList>

#include "snippet.h"
#include "snippet_search_pattern.h"

/** @brief Database operations interface. Implemented by SnippetRepositoryConcrete. */
class SnippetRepositoryInterface
{
public:
    /** Saves snippet to a database. @param s Snippet to be saved in a database */
    virtual void saveSnippet(Snippet &s) = 0;
    /** Retrieves 5 most recently saved snippets from database */
    virtual QList<Snippet> pullSnippets() = 0;
    /** Retrives snippets (max 5) matching pattern. @param pattern Pattern for snippets to match. */
    virtual QList<Snippet> pullSnippets(SnippetSearchPattern &pattern) = 0;
};

#endif