#ifndef SNIPPET_H
#define SNIPPET_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include <string>
#include <map>

class Snippet : public QObject
{

    Q_OBJECT

public:
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

    QJsonObject toJson() const;
    static Snippet fromJson(QJsonObject &obj);
    static Snippet fromJson(QJsonObject &&obj);

    void setAuthor(QString author);
    void setTitle(QString title);
    void setCreated(QDateTime created);
    void setLang(QString lang);
    void setContent(QString content);

    QString author() const;
    QString title() const;
    QDateTime created() const;
    QString lang() const;
    QString content() const;

    static QString fieldToString(Field field);
    static int fieldToItsMaxLength(Field field);

    static const int MAX_AUTHOR_LEN = 30;
    static const int MAX_TITLE_LEN = 100;
    static const int MAX_LANG_LEN = 20;
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

#endif
