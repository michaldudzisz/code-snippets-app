#ifndef SNIPPET_H
#define SNIPPET_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include <string>
#include <map>
#include <QVariant>

/** @brief Snippet class containg: 
 * author, title, creation date-time, programming language and content.
 */

class Snippet : public QObject
{

    Q_OBJECT

public:
    /** @brief Enumeration of snippet fields. */
    enum Field
    {
        AUTHOR,
        TITLE,
        CREATED,
        LANG,
        CONTENT
    };

    Snippet();
    Snippet(const Snippet &s);
    Snippet(QString author, QString title, QString lang, QString content = 0);
    Snippet(QString author, QString title, QDateTime created, QString lang, QString content = 0);

    Snippet &operator=(const Snippet &s);
    bool operator==(const Snippet &s);

    /** Checks wheter a snippet JSON object is valid (contains all the necessary fields
     * which are in appropriate format) */
    static void validateSnippetJson(QJsonObject &obj);
    /** Serializes a snippet object into a JSON object */
    QJsonObject toJson() const;
    /** Retrieves a snippet object from a JSON object */
    static Snippet fromJson(QJsonObject &obj);
    /** Retrieves a snippet object from a JSON object */
    static Snippet fromJson(QJsonObject &&obj);

    /** Converts into a variant contating a snippet object */
    QVariant toVariant() const;

    /** Sets author. May throw TooLongContentException if author is too long */
    void setAuthor(QString author);
    /** Sets title. May throw TooLongContentException if title is too long */
    void setTitle(QString title);
    /** Sets creation date. */
    void setCreated(QDateTime created);
    /** Sets programming language. May throw TooLongContentException if language is 
     * too long or UnsupportedLanguageException if language is not allowed */
    void setLang(QString lang);
    /** Sets content. May throw TooLongContentException if content is too long */
    void setContent(QString content);

    /** Returns author */
    QString author() const;
    /** Returns title */
    QString title() const;
    /** Returns creation date */
    QDateTime created() const;
    /** Returns programming language of snippet */
    QString lang() const;
    /** Returns author */
    QString content() const;

    /** Returns list of allowed snippet programming languages */
    static QStringList availableLangs();

    /** Returns string representing given enum, eg. for JSON serialization. */
    static QString fieldToString(Field field);
    /** Returns max length of given field */
    static int fieldToItsMaxLength(Field field);

    /** Max author string legth */
    static const int MAX_AUTHOR_LEN = 30;
    /** Max title string legth */
    static const int MAX_TITLE_LEN = 100;
    /** Max programming language string length */
    static const int MAX_LANG_LEN = 20;
    /** Max snippet content string lenght */
    static const int MAX_CONTENT_LEN = 1000;

private:
    QString author_;
    QString title_;
    QDateTime created_;
    QString lang_;
    QString content_;

    static QStringList availableLangs_;

    static const QHash<Field, QString> fieldToStringMap;

    static const QHash<Field, int> fieldToItsMaxLengthMap;
};

Q_DECLARE_METATYPE(Snippet);

#endif

