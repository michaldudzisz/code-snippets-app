#ifndef SNIPPET_SEARCH_PATTERN
#define SNIPPET_SEARCH_PATTERN

#include <QObject>
#include <QString>
#include <QDateTime>

struct SnippetSearchPattern : QObject
{
    Q_OBJECT

public:

    SnippetSearchPattern();
    SnippetSearchPattern(const SnippetSearchPattern & other);
    SnippetSearchPattern &operator=(const SnippetSearchPattern &);
    ~SnippetSearchPattern() = default;

    QString authorSQLiteSubsequence() const;
    QString titleSQLiteSubsequence() const;
    QString languageSQLite() const;

    bool isEmpty() const;

    void setAuthorSubsequence(const QString &author);
    void setTitleSubsequence(const QString &title);
    void setCreatedFrom(const QDateTime &from);
    void setCreatedTo(const QDateTime &to);
    void setLang(const QString &lang);

    QString authorSubsequence() const;
    QString titleSubsequence() const;
    QDateTime createdFrom() const;
    QDateTime createdTo() const;
    QString lang() const;

private:

    QString authorSubsequence_;
    QString titleSubsequence_;
    QDateTime createdFrom_;
    QDateTime createdTo_;
    QString lang_;

    static const QString SQLITE_SEQ_CHAR;
};

#endif