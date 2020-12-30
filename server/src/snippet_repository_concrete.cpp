#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QCoreApplication>

#include "snippet_repository_concrete.h"

SnippetRepositoryConcrete SnippetRepositoryConcrete::instance_;

SnippetRepositoryConcrete &SnippetRepositoryConcrete::getInstance()
{
    return instance_;
}

void SnippetRepositoryConcrete::setDatabasePath(QString &path)
{
    databasePath_ = path;
}

SnippetRepositoryConcrete::SnippetRepositoryConcrete()
{/*
    QFile path_file(serverDirLocationFilePath_);
    if (!path_file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::exception();

    if (path_file.atEnd())
        throw std::exception();

    QByteArray path_bytes = path_file.readLine();
    QString path(path_bytes);*/
    QString app_path = QCoreApplication::applicationDirPath();
    QString database_path = app_path + databasePathFromAppDir_;
    setDatabasePath(database_path);
}

void SnippetRepositoryConcrete::saveSnippet(Snippet &s)
{
    // make a connection
    QSqlDatabase db = openedConnection();
    // get query
    QSqlQuery query = prepareInsertQuery(db, s);
    // execute sql
    query.exec();
    // close connection
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
/*
QString SnippetRepositoryConcrete::databaseName()
{
    return databaseName_;
}*/

QDir SnippetRepositoryConcrete::databasePath()
{
    return databasePath_;
}

QVariant SnippetRepositoryConcrete::findSnippetsByTitle(QString &phrase)
{
    QVariant TODO;
    return TODO;
}

