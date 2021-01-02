#ifndef SNIPPET_REPOSITORY_CONCRETE
#define SNIPPET_REPOSITORY_CONCRETE

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QVariant>

#include "snippet_repository_interface.h"
#include "snippet_search_pattern.h"

class SnippetRepositoryConcrete : public QObject, public SnippetRepositoryInterface
{
    Q_OBJECT

public:
    SnippetRepositoryConcrete(SnippetRepositoryConcrete &other) = delete;
    void operator=(const SnippetRepositoryConcrete &other) = delete;
    ~SnippetRepositoryConcrete();

    static QSharedPointer<SnippetRepositoryConcrete> getInstance();

    void saveSnippet(Snippet &s) override;
    QList<QVariant> pullSnippets() override;
    QList<QVariant> pullSnippets(SnippetSearchPattern &pattern) override;

protected:
    SnippetRepositoryConcrete();

    void setDatabasePath(QString &path);
    QSqlDatabase database();

    QDir databasePath();
    void openDatabase();
    void closeDatabase();
    void executeQuery(QSqlQuery query);
    QVariant mapQueryRowToSnippet(const QSqlQuery &query);
    static const char *errorToCString(QSqlError &err);

    template<typename Func>
    void iterateOverQueryResults(QSqlQuery &query, QList<QVariant> &snippets, Func func);

    QSqlQuery prepareInsertQuery(const Snippet &s);
    QSqlQuery preparePullLastQuery();
    QSqlQuery prepareSelectByFieldsQuery(const SnippetSearchPattern &pattern);

    static QWeakPointer<SnippetRepositoryConcrete> instance_;
    QSqlDatabase database_;

    const QString databasePathFromAppDir_ = "/../database/snippet_db.db";
    QDir databasePath_;

    const QString DATABASE_TYPE = "QSQLITE";

    const QString INSERT_QUERY =
        "INSERT INTO snippets (author, title, created, language, content) "
        "VALUES (:author, :title, :created, :language, :content);";
    const QString BIND_AUTHOR = ":author";
    const QString BIND_TITLE = ":title";
    const QString BIND_CREATED = ":created";
    const QString BIND_LANGUAGE = ":language";
    const QString BIND_CONTENT = ":content";

    const QString PULL_QUERY =
        "SELECT author, title, created, language, content, id FROM snippets "
        "ORDER BY id DESC "
        "LIMIT 5;";

    const QString SELECT_BY_FIELDS =
        "SELECT author, title, created, language, content, id FROM snippets "
        "WHERE "
        "author LIKE :author_subsequence AND "
        "title LIKE :title_subsequence AND "
        "language LIKE :specified_lang "
        "ORDER BY id DESC "
        "LIMIT 5;";
    const QString BIND_AUTHOR_SUBSEQUENCE = ":author_subsequence";
    const QString BIND_TITLE_SUBSEQUENCE = ":title_subsequence";
    const QString BIND_SPECIFIED_LANG = ":specified_lang";
};

#endif

