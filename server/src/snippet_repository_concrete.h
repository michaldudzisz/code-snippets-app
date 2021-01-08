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

/** @brief Singleton implementation of SnippetRepositoryInterface. Responsible for database access */

class SnippetRepositoryConcrete : public QObject, public SnippetRepositoryInterface
{
    Q_OBJECT

public:
    /** As for a singleton, assignment operator is prohibited */
    SnippetRepositoryConcrete(SnippetRepositoryConcrete &other) = delete;
    /** As for a singleton, copying constructor is prohibited */
    void operator=(const SnippetRepositoryConcrete &other) = delete;
    
    ~SnippetRepositoryConcrete();

    /** Retrieves a singleton instance. 
     * @return Shared pointer to a singleton's instance 
     */
    static QSharedPointer<SnippetRepositoryConcrete> getInstance();

    /** Implementation of SnippetRepositoryInterface#saveSnippet()
     * Saves snippet to a database.
     * @param s Snippet to be saved in a database.
     * @see SnippetRepositoryInterface#saveSnippet
     */ 
    void saveSnippet(Snippet &s) override;

    /** Implementation of SnippetRepositoryInterface#pullSnippets()
     * Retrieves up to 5 last saved to database snippets.
     * @see SnippetRepositoryInterface#pullSnippets
     */ 
    QList<Snippet> pullSnippets() override;

    /** Implementation of SnippetRepositoryInterface#pullSnippets(SnippetSearchPattern &)
     * Retrieves up to 5 snippets matching to given pattern.
     * @param pattern Pattern for snippets to be matched to.
     * @see SnippetRepositoryInterface#pullSnippets
     */ 
    QList<Snippet> pullSnippets(SnippetSearchPattern &pattern) override;

protected:
    SnippetRepositoryConcrete();

    QList<QVariant> pullFromDatabase(SnippetSearchPattern &pattern);

    QList<Snippet> parseSnippetsFromVariantList(QList<QVariant> list);

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
        "language LIKE :specified_lang AND "
        "created BETWEEN :created_from AND :created_to "
        "ORDER BY id DESC "
        "LIMIT 5;"; 
    const QString BIND_AUTHOR_SUBSEQUENCE = ":author_subsequence";
    const QString BIND_TITLE_SUBSEQUENCE = ":title_subsequence";
    const QString BIND_CREATED_FROM = ":created_from";
    const QString BIND_CREATED_TO = ":created_to";
    const QString BIND_SPECIFIED_LANG = ":specified_lang";
};

#endif

