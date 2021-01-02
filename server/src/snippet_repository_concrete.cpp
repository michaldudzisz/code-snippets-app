#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QCoreApplication>
#include <QList>
#include <QDebug>

#include "snippet_repository_concrete.h"

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

void SnippetRepositoryConcrete::setDatabasePath(QString &path)
{
    databasePath_ = path;
}

SnippetRepositoryConcrete::SnippetRepositoryConcrete()
{
    QString app_path = QCoreApplication::applicationDirPath();
    QString database_path = app_path + databasePathFromAppDir_;

    setDatabasePath(database_path);
}

void SnippetRepositoryConcrete::saveSnippet(Snippet &s)
{

    QSqlDatabase db = openedConnection();

    QSqlQuery query = prepareInsertQuery(db, s);

    query.exec();

    db.close();
}

QSqlDatabase SnippetRepositoryConcrete::openedConnection()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(databasePath().path());
    database.open();
    return database;
}

QSqlQuery SnippetRepositoryConcrete::prepareInsertQuery(
    const QSqlDatabase &database,
    const Snippet &s) const
{
    QSqlQuery query(database);

    query.prepare("INSERT INTO snippets (author, title, created, language, content) "
                  "VALUES (:author, :title, :created, :language, :content)");

    query.bindValue(":author", s.author());
    query.bindValue(":title", s.title());
    query.bindValue(":created", s.created().toString());
    query.bindValue(":language", s.lang());
    query.bindValue(":content", s.content());

    return query;
}

QDir SnippetRepositoryConcrete::databasePath()
{
    return databasePath_;
}

QList<QVariant> SnippetRepositoryConcrete::findSnippetsByTitle(const QString &phrase)
{
    QList<QVariant> snippets;

    QSqlDatabase database = openedConnection();

    QSqlQuery query(SELECT_BY_TITLE_QUERY, database);
    query.bindValue(TITLE_SUBSEQUENCE, phrase);

    query.exec();

    query.first();
    do
    {
        // tutaj try catch
        Snippet snipp = mapQueryRowToSnippet(query);
        // i jeśli się nie da, to pusty snippet idzie do qvariant
        // albo nic idzie do qvariant
        // zaleznie od tego, jak dziala qvariant

        snippets.append(snipp.toVariant());

    } while (query.next());

    database.close();

    return snippets;
}

QList<QVariant> SnippetRepositoryConcrete::pullSnippets()
{
    QList<QVariant> snippets;

    QSqlDatabase database = openedConnection();

    QSqlQuery query(PULL_QUERY, database);

    query.exec();

    query.first();
    do
    {
        // tutaj try catch
        Snippet snipp = mapQueryRowToSnippet(query);
        // i jeśli się nie da, to pusty snippet idzie do qvariant
        // albo nic idzie do qvariant
        // zaleznie od tego, jak dziala qvariant

        snippets.append(snipp.toVariant());

    } while (query.next());

    database.close();

    return snippets;
}

Snippet SnippetRepositoryConcrete::mapQueryRowToSnippet(const QSqlQuery &query)
{
    QString author = query.value(0).toString();
    QString title = query.value(1).toString();
    QDateTime created = QDateTime::fromString(query.value(2).toString());
    QString lang = query.value(3).toString();
    QString content = query.value(4).toString();

    Snippet snipp(author, title, created, lang, content);
    return snipp;
}

QList<QVariant> SnippetRepositoryConcrete::findSnippetsByLanguage(const QString &lang)
{
    QList<QVariant> snippets;

    QSqlDatabase database = openedConnection();

    QSqlQuery query(SELECT_BY_LANG_QUERY, database);
    query.bindValue(SPECIFIED_LANG, lang);

    query.exec();

    query.first();
    do
    {
        // tutaj try catch
        Snippet snipp = mapQueryRowToSnippet(query);
        // i jeśli się nie da, to pusty snippet idzie do qvariant
        // albo nic idzie do qvariant
        // zaleznie od tego, jak dziala qvariant

        snippets.append(snipp.toVariant());

    } while (query.next());

    database.close();

    return snippets;
}

QList<QVariant> SnippetRepositoryConcrete::findSnippetsByFields(
    const SnippetSearchPattern &pattern)
{
    QList<QVariant> snippets;

    QSqlDatabase database = openedConnection();

    QSqlQuery query = prepareSelectByFieldsQuery(database, pattern);

    query.exec();

    query.first();
    do
    {
        // tutaj try catch
        Snippet snipp = mapQueryRowToSnippet(query);
        // i jeśli się nie da, to pusty snippet idzie do qvariant
        // albo nic idzie do qvariant
        // zaleznie od tego, jak dziala qvariant

        snippets.append(snipp.toVariant());

    } while (query.next());

    database.close();

    return snippets;
}

QSqlQuery SnippetRepositoryConcrete::prepareSelectByFieldsQuery(
    const QSqlDatabase &database,
    const SnippetSearchPattern &pattern) const
{
    QSqlQuery query(SELECT_BY_FIELDS, database);

    query.bindValue(":author_subsequence", QString("rname"));
    query.bindValue(TITLE_SUBSEQUENCE, "some");
    query.bindValue(SPECIFIED_LANG, "c++");

    qDebug() << query.lastQuery();
    qDebug() << "xd";
    qDebug() << query.boundValue(":author_subsequence");
    return query;
}
