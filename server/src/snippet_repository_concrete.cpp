#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QCoreApplication>
#include <cstdio>

#include "snippet_repository_concrete.h"

QWeakPointer<SnippetRepositoryConcrete> SnippetRepositoryConcrete::instance_;

QSharedPointer<SnippetRepositoryConcrete> SnippetRepositoryConcrete::getInstance()
{
    QSharedPointer<SnippetRepositoryConcrete> ptr_to_return;

    if (instance_.isNull())
    {
        ptr_to_return = QSharedPointer<SnippetRepositoryConcrete>(new SnippetRepositoryConcrete());
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
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databasePath().path());
    db.open();
    return db;
}

QSqlQuery SnippetRepositoryConcrete::prepareInsertQuery(
    const QSqlDatabase &db,
    const Snippet &s) const
{
    QSqlQuery query(db);

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

QVariant SnippetRepositoryConcrete::findSnippetsByTitle(QString &phrase)
{
    QVariant TODO;
    return TODO;
}
