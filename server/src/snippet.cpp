#include <algorithm>

#include "snippet.h"
#include "too_long_content_exception.h"
#include "invalid_snippet_json_exception.h"
#include "unsupported_language_exception.h"

Snippet::Snippet()
{
    created_ = QDateTime::currentDateTime();
}

Snippet::Snippet(const Snippet &s) : QObject()
{
    setAuthor(s.author());
    setCreated(s.created());
    setLang(s.lang());
    setContent(s.content());
}

Snippet::Snippet(QString author, QString lang, QString content)
{
    setAuthor(author);
    created_ = QDateTime::currentDateTime();
    setLang(lang);
    setContent(content);
}

Snippet::Snippet(QString author, QDateTime created, QString lang, QString content)
{
    setAuthor(author);
    setCreated(created);
    setLang(lang);
    setContent(content);
}

void Snippet::setAuthor(QString author)
{
    if (author.length() > MAX_AUTHOR_LEN)
        throw TooLongContentException(Snippet::Field::AUTHOR, author.length());
    author_ = author;
}

void Snippet::setCreated(QDateTime created)
{
    created_ = created;
}

void Snippet::setLang(QString lang)
{
    if (lang.length() > MAX_LANG_LEN)
        throw TooLongContentException(Snippet::Field::LANG, lang.length());

    if (!availableLangs_.contains(lang))
        throw UnsupportedLanguageException(lang.toUtf8().constData()); // moze nie dzialac na windowsie

    lang_ = lang;
}

void Snippet::setContent(QString content)
{
    if (content.length() > MAX_CONTENT_LEN)
        throw TooLongContentException(Snippet::Field::CONTENT, content.length());

    content_ = content;
}

QString Snippet::author() const
{
    return author_;
}

QDateTime Snippet::created() const
{
    return created_;
}

QString Snippet::lang() const
{
    return lang_;
}

QString Snippet::content() const
{
    return content_;
}

QJsonObject Snippet::toJson() const
{
    QJsonObject json_obj;

    json_obj.insert(QString(fieldToString(Snippet::Field::AUTHOR)), author_);
    json_obj.insert(QString(fieldToString(Snippet::Field::CREATED)), created_.toString());
    json_obj.insert(QString(fieldToString(Snippet::Field::LANG)), lang_);
    json_obj.insert(QString(fieldToString(Snippet::Field::CONTENT)), content_);

    return json_obj;
}

Snippet Snippet::fromJson(QJsonObject &obj)
{
    for (int field_int = Snippet::Field::AUTHOR; field_int < Snippet::Field::CONTENT; ++field_int)
    {
        if (!obj.contains(fieldToString(static_cast<Snippet::Field>(field_int))) ||
            !obj.value(fieldToString(static_cast<Snippet::Field>(field_int))).isString())
            throw InvalidSnippetJsonException();
    }

    QString author = obj.value(Snippet::fieldToString(Snippet::Field::AUTHOR)).toString();
    QDateTime created = QDateTime::fromString(obj.value(Snippet::fieldToString(Snippet::Field::CREATED)).toString());
    QString lang = obj.value(Snippet::fieldToString(Snippet::Field::LANG)).toString();
    QString content = obj.value(Snippet::fieldToString(Snippet::Field::CONTENT)).toString();

    Snippet snippet(author, created, lang, content);

    return snippet;
}

Snippet Snippet::fromJson(QJsonObject &&obj)
{
    return Snippet::fromJson(obj);
}

const char *Snippet::fieldToString(Snippet::Field field)
{
    return fieldToStringMap[field];
}

int Snippet::fieldToItsMaxLength(Snippet::Field field)
{
    return fieldToItsMaxLengthMap[field];
}

const QHash<Snippet::Field, const char *> Snippet::fieldToStringMap =
    {{Field::AUTHOR, "author"},
     {Field::CREATED, "created"},
     {Field::LANG, "lang"},
     {Field::CONTENT, "content"}};

const QHash<Snippet::Field, int> Snippet::fieldToItsMaxLengthMap =
    {{Field::AUTHOR, MAX_AUTHOR_LEN},
     {Field::LANG, MAX_LANG_LEN},
     {Field::CONTENT, MAX_CONTENT_LEN}};

QStringList Snippet::availableLangs_ = {"c++", "python", "javascript"};

Snippet &Snippet::operator=(const Snippet &s)
{
    setAuthor(s.author());
    setCreated(s.created());
    setLang(s.lang());
    setContent(s.content());

    return *this;
}
