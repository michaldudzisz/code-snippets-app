#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QCoreApplication>
#include <QList>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

#include "snippet_repository_concrete.h"
#include "query_not_performed_exception.h"
#include "repository_not_initialized_exception.h"

QWeakPointer<SnippetRepositoryConcrete> SnippetRepositoryConcrete::instance_;

QSharedPointer<SnippetRepositoryConcrete> SnippetRepositoryConcrete::getInstance()
{
    QSharedPointer<SnippetRepositoryConcrete> ptr_to_return;

    if (instance_.isNull())
    {
        ptr_to_return = QSharedPointer<SnippetRepositoryConcrete>(
            new SnippetRepositoryConcrete());
        instance_ = QWeakPointer<SnippetRepositoryConcrete>(ptr_to_return);
    }
    else
    {
        ptr_to_return = instance_.toStrongRef();
    }

    return ptr_to_return;
}

SnippetRepositoryConcrete::SnippetRepositoryConcrete()
{
    QString app_path = QCoreApplication::applicationDirPath();
    QString database_path = app_path + databasePathFromAppDir_;
    setDatabasePath(database_path);

    database_ = QSqlDatabase::addDatabase(DATABASE_TYPE);
    database_.setDatabaseName(databasePath().path());
}

SnippetRepositoryConcrete::~SnippetRepositoryConcrete()
{
    QSqlDatabase::removeDatabase(database().databaseName());
}

QList<Snippet> SnippetRepositoryConcrete::pullSnippets()
{
    SnippetSearchPattern empty_pattern;
    return pullSnippets(empty_pattern);
}

QList<Snippet> SnippetRepositoryConcrete::pullSnippets(SnippetSearchPattern &pattern)
{
    QList<QVariant> snippet_var = pullFromDatabase(pattern);
    return parseSnippetsFromVariantList(snippet_var);
}

QList<Snippet> SnippetRepositoryConcrete::parseSnippetsFromVariantList(QList<QVariant> var_list)
{
    QList<Snippet> snippet_list;
    for (QVariant var : var_list)
    {
        if (var.isNull())
            continue; 
        // ^ do bazy danych zapisano snippet, ktorego nie da sie odtworzyc
        // warto zrobic loga

        snippet_list.append(var.value<Snippet>());
    }
    return snippet_list;
}

void SnippetRepositoryConcrete::setDatabasePath(QString &path)
{
    databasePath_ = path;
}

void SnippetRepositoryConcrete::saveSnippet(Snippet &snipp)
{
    openDatabase();
    QSqlQuery query = prepareInsertQuery(snipp);
    executeQuery(query);
    closeDatabase();
}

QSqlQuery SnippetRepositoryConcrete::prepareInsertQuery(const Snippet &snipp)
{
    QSqlQuery query(database());

    query.prepare(INSERT_QUERY);

    query.bindValue(BIND_AUTHOR, snipp.author());
    query.bindValue(BIND_TITLE, snipp.title());
    query.bindValue(BIND_CREATED, snipp.created().toSecsSinceEpoch());
    query.bindValue(BIND_LANGUAGE, snipp.lang());
    query.bindValue(BIND_CONTENT, snipp.content());

    return query;
}

QDir SnippetRepositoryConcrete::databasePath()
{
    return databasePath_;
}

QSqlQuery SnippetRepositoryConcrete::preparePullLastQuery()
{
    QSqlQuery query(database());
    query.prepare(PULL_QUERY);
    return query;
}

QVariant SnippetRepositoryConcrete::mapQueryRowToSnippet(const QSqlQuery &query)
{
    QString author, title, lang, content;
    QDateTime created;

    if (query.isValid())
    {
        author = query.value(0).toString();
        title = query.value(1).toString();
        created = QDateTime::fromSecsSinceEpoch(query.value(2).toLongLong());
        lang = query.value(3).toString();
        content = query.value(4).toString();
    }

    QVariant result;
    try
    {
        Snippet snipp(author, title, created, lang, content);
        result.setValue(snipp);
    }
    catch (std::exception &ignored)
    {
        // may be ignored, because snippet goes to variant and must be checked later
    }

    return result;
}

QList<QVariant> SnippetRepositoryConcrete::pullFromDatabase(SnippetSearchPattern &pattern)
{
    QList<QVariant> snippets;
    QSqlQuery query;

    openDatabase();

    if (pattern.isEmpty())
        query = preparePullLastQuery();
    else
        query = prepareSelectByFieldsQuery(pattern);

    executeQuery(query);

    iterateOverQueryResults(query, snippets, 
    [this, query](QSqlQuery &q, QList<QVariant> &snippets) {
        QVariant snipp = mapQueryRowToSnippet(query);
        snippets.append(snipp);
    });

    closeDatabase();

    return snippets;
}

QSqlQuery SnippetRepositoryConcrete::prepareSelectByFieldsQuery(
    const SnippetSearchPattern &pattern)
{
    QSqlQuery query(database());
    query.prepare(SELECT_BY_FIELDS);
    query.bindValue(BIND_AUTHOR_SUBSEQUENCE, pattern.authorSQLiteSubsequence());
    query.bindValue(BIND_TITLE_SUBSEQUENCE, pattern.titleSQLiteSubsequence());
    query.bindValue(BIND_CREATED_FROM, pattern.createdFromSQLite());
    query.bindValue(BIND_CREATED_TO, pattern.createdToSQLite());
    query.bindValue(BIND_SPECIFIED_LANG, pattern.languageSQLite());

    return query;
}

void SnippetRepositoryConcrete::openDatabase()
{
    if (!database().open())
        throw QueryNotPerformedException("Unable to open connection with database.");
}

void SnippetRepositoryConcrete::closeDatabase()
{
    database().close();
}

QSqlDatabase SnippetRepositoryConcrete::database()
{
    return database_;
}

void SnippetRepositoryConcrete::executeQuery(QSqlQuery query)
{
    if (!query.exec())
    {
        closeDatabase();
        QSqlError err = query.lastError();
        throw QueryNotPerformedException(errorToCString(err));
    }
}

const char *SnippetRepositoryConcrete::errorToCString(QSqlError &err)
{
    return err.text().toLocal8Bit().data();
}

template <typename Func>
void SnippetRepositoryConcrete::iterateOverQueryResults(
    QSqlQuery &query, QList<QVariant> &snippets, Func func)
{
    query.first();
    do
    {
        func(query, snippets);
    } while (query.next());
}
