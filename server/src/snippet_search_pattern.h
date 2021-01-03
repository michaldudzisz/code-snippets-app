#ifndef SNIPPET_SEARCH_PATTERN
#define SNIPPET_SEARCH_PATTERN

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QJsonObject>

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
    qint64 createdFromSQLite() const;
    qint64 createdToSQLite() const;
    QString languageSQLite() const;

    bool isEmpty() const;
    static SnippetSearchPattern fromJson(QJsonObject &obj);
    static SnippetSearchPattern fromJson(QJsonObject &&obj);
    QJsonObject toJson() const;
    static QJsonValue dateToJsonValue(const QDateTime &date);
    static QDateTime parseDateTime(const QJsonValue &val);
    static QDateTime parseDateTime(const QJsonValue &&val);
    static void validateJson(const QJsonObject &obj);

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

    static const QString AUTHOR_JSON_FIELD;
    static const QString TITLE_JSON_FIELD;
    static const QString CREATED_FROM_JSON_FIELD;
    static const QString CREATED_TO_JSON_FIELD;
    static const QString LANG_JSON_FIELD;

};

#endif