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
     * @param query QueryStringMap from url */
    static SnippetSearchPattern fromQueryString(const QueryStringMap &query);

    /** Parses created_from or created_to string placed in query string 
     *  into QDateTime object 
     * @param query String of value of field created_from or created_to 
     * in the query string from url */
    static QDateTime queryStringToDateTime(const QString &query);

    /** Parses created_from or created_to string placed in query string 
     *  into QDateTime object 
     * @param query String of value of field created_from or created_to 
     * in the query string from url */
    static QDateTime queryStringToDateTime(const QString &&query);

    /** Parses JSON object into a SnippetSearchPattern 
     * @param obj JSON object to be parsed */
    static SnippetSearchPattern fromJson(QJsonObject &obj);

    /** Parses JSON object into a SnippetSearchPattern 
     * @param obj JSON object to be parsed */
    static SnippetSearchPattern fromJson(QJsonObject &&obj);

    /** Serializes SnippeSearchPattern object into a JSON object */
    QJsonObject toJson() const;

    /** Serializes date object into a secs-since-unix-epoch format or json NULL */
    static QJsonValue dateToJsonValue(const QDateTime &date);
    /** Parses QDateTime from its JSON value */
    static QDateTime parseDateTime(const QJsonValue &val);
    /** Parses QDateTime from its JSON value */
    static QDateTime parseDateTime(const QJsonValue &&val);
    /** Checks wether JSON object with SnippetSearchPattern is valid 
     * (contains all necessary fields and fields are appropriate format) */
    static void validateJson(const QJsonObject &obj);

    /** Sets author subsequence, that will be looked for. 
     * @param author Must fullfil all the conditions for author in Snippet class */
    void setAuthorSubsequence(const QString &author);
    /** Sets title subsequence, that will be looked for. 
     * @param title Must fullfil all the conditions for title in Snippet class */
    void setTitleSubsequence(const QString &title);
    /** Sets creation date, from which server will start to search snippets. */
    void setCreatedFrom(const QDateTime &from);
    /** Sets creation date, to which server will search snippets. */
    void setCreatedTo(const QDateTime &to);
    /** Sets programming language, that will be looked for. 
     * @param lang Must be one of allowed languages */
    void setLang(const QString &lang);

    /** Returns author subseqence that has been set earlier */
    QString authorSubsequence() const;
    /** Returns title subseqence that has been set earlier */
    QString titleSubsequence() const;
    /** Returns creation from which to search that has been set earlier */
    QDateTime createdFrom() const;
    /** Returns creation to which to search that has been set earlier */
    QDateTime createdTo() const;
    /** Returns programming language that has been set earlier */
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