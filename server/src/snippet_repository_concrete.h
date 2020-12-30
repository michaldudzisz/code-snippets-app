#ifndef SNIPPET_REPOSITORY_CONCRETE
#define SNIPPET_REPOSITORY_CONCRETE

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>

#include "snippet_repository_interface.h"

class SnippetRepositoryConcrete : public QObject, public SnippetRepositoryInterface
{
    Q_OBJECT

public:
    static SnippetRepositoryConcrete &getInstance();

    SnippetRepositoryConcrete(SnippetRepositoryConcrete &other) = delete;
    
    void operator=(const SnippetRepositoryConcrete &other) = delete;

    void saveSnippet(Snippet &s) override;
    QVariant findSnippetsByTitle(QString &phrase) override;

protected:
    SnippetRepositoryConcrete();
    void setDatabasePath(QString &path);

    //QString databaseName();
    QDir databasePath();
    QSqlDatabase openedConnection();
    QSqlQuery prepareInsertQuery(const QSqlDatabase &db, const Snippet &s) const;

    static SnippetRepositoryConcrete instance_;
    const QString databasePathFromAppDir_ = "../database/snippet_db.db";
    //const QString serverDirLocationFile_ = ""
    QDir databasePath_;
};

#endif