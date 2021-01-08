#ifndef SNIPPET_SEARCH_PATTERN
#define SNIPPET_SEARCH_PATTERN

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QJsonObject>

#include "qhttpengine/socket.h"

typedef QHttpEngine::Socket::QueryStringMap QueryStringMap;

/** @brief Pattern structure containing:
 * author subseqence, 
 * title subsequence,
 * creation time from which the search will be started,
 * creation time to which the snippets will be searched,
 * specified language.
 * All the fields are unnecessary, all may be freely combined. */

struct SnippetSearchPattern : QObject
{
    Q_OBJECT

public:
    /** Default constructor. Sets no fields. */
    SnippetSearchPattern();
    SnippetSearchPattern(const SnippetSearchPattern & other);
    SnippetSearchPattern &operator=(const SnippetSearchPattern &);
    ~SnippetSearchPattern() = default;

    /** @return Author subsequence in a string, that can be passed right into a SQLite query. 
     * May contain SQLite specific characters, like wildcards. */ 
    QString authorSQLiteSubsequence() const;

    /** @return Title subsequence in a string, that can be passed right into a SQLite query. 
     * May contain SQLite specific characters, like wildcards. */ 
    QString titleSQLiteSubsequence() const;

    /** @return Created from as a number, that can be passed right into a SQLite query. 
     * May contain SQLite specific characters, like wildcards. */ 
    qint64 createdFromSQLite() const;

    /** @return Created to as a number, that can be passed right into a SQLite query. 
     * May contain SQLite specific characters, like wildcards. */ 
    qint64 createdToSQLite() const;

    /** @return Programming language as a string, that cann be passed right into a SQLite query. 
     * May contain SQLite specific characters, like wildcards. */ 
    QString languageSQLite() const;

    /** Checks if all pattern's fields are empty or not */
    bool isEmpty() const;
    /** Pareses URL query string into a SnippetSearchPattern object. May throw 
     * InvalidGetRequestBody exception if the query string is invalid.
     * */
    static SnippetSearchPattern fromQueryString(const QueryStringMap &query);
    static QDateTime queryStringToDateTime(const QString &query);
    static QDateTime queryStringToDateTime(const QString &&query);
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