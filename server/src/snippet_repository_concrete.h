#ifndef SNIPPET_REPOSITORY_CONCRETE
#define SNIPPET_REPOSITORY_CONCRETE

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QSharedPointer>
#include <QWeakPointer>

#include "snippet_repository_interface.h"
#include "snippet_search_pattern.h"

class SnippetRepositoryConcrete : public QObject, public SnippetRepositoryInterface
{
    Q_OBJECT

public:
    static QSharedPointer<SnippetRepositoryConcrete> getInstance();

    SnippetRepositoryConcrete(SnippetRepositoryConcrete &other) = delete;

    void operator=(const SnippetRepositoryConcrete &other) = delete;

    void saveSnippet(Snippet &s) override;
    QList<QVariant> pullSnippets() override;
    QList<QVariant> findSnippetsByFields(const SnippetSearchPattern &pattern) override;
    QList<QVariant> findSnippetsByTitle(const QString &phrase) override;
    QList<QVariant> findSnippetsByLanguage(const QString &lang) override;

protected:
    SnippetRepositoryConcrete();

    void setDatabasePath(QString &path);

    QDir databasePath();
    QSqlDatabase openedConnection();

    Snippet mapQueryRowToSnippet(const QSqlQuery &query);

    QSqlQuery prepareInsertQuery(const QSqlDatabase &db, const Snippet &s) const;
    QSqlQuery prepareSelectByFieldsQuery(const QSqlDatabase &db, const SnippetSearchPattern &pattern) const;

    static QWeakPointer<SnippetRepositoryConcrete> instance_;

    const QString databasePathFromAppDir_ = "/../database/snippet_db.db";
    QDir databasePath_;

    const QString PULL_QUERY =
        "SELECT author, title, created, language, content, id FROM snippets "
        "ORDER BY id DESC "
        "LIMIT 5;";

    const QString SELECT_BY_TITLE_QUERY =
        "SELECT author, title, created, language, content, id FROM snippets "
        "WHERE title LIKE %:title_subsequence% "
        "ORDER BY id DESC "
        "LIMIT 5;";
    

    const QString SELECT_BY_LANG_QUERY =
        "SELECT author, title, created, language, content, id FROM snippets "
        "WHERE language LIKE :specified_lang "
        "ORDER BY id DESC "
        "LIMIT 5;";
    

    const QString SELECT_BY_FIELDS =
        "SELECT author, title, created, language, content, id FROM snippets "
        "WHERE "
        "author LIKE :author_subsequence AND "
        "title LIKE '%:title_subsequence%' AND "
        "language LIKE ':specified_lang' "
        "ORDER BY id DESC "
        "LIMIT 5;";
    const QString AUTHOR_SUBSEQUENCE = ":author_subsequence";
    const QString TITLE_SUBSEQUENCE = ":title_subsequence";
    const QString SPECIFIED_LANG = ":specified_lang";
};

#endif
/*
SELECT author, title, created, language, content, id FROM snippets 
WHERE 
author LIKE '%erna%' AND 
title LIKE '%some%' AND 
language LIKE 'c++' 
ORDER BY id DESC 
LIMIT 5; 

SELECT author, title, created, language, content, id FROM snippets 
WHERE 
author LIKE '%erna%' AND 
title LIKE '%some%' AND 
language LIKE 'c++' 
ORDER BY id DESC 
LIMIT 5; 

*/
