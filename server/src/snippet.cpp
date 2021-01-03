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
    setTitle(s.title());
    setCreated(s.created());
    setLang(s.lang());
    setContent(s.content());
}

Snippet::Snippet(QString author, QString title, QString lang, QString content)
{
    setAuthor(author);
    setTitle(title);
    created_ = QDateTime::currentDateTime();
    setLang(lang);
    setContent(content);
}

Snippet::Snippet(QString author, QString title, QDateTime created, QString lang, QString content)
{
    setAuthor(author);
    setTitle(title);
    setCreated(created);
    setLang(lang);
    setContent(content);
}

void Snippet::setAuthor(QString author)
{
    if (author.length() > MAX_AUTHOR_LEN)
        throw TooLongContentException(Field::AUTHOR, author.length());
    author_ = author;
}

void Snippet::setTitle(QString title)
{
    if (title.length() > MAX_TITLE_LEN)
        throw TooLongContentException(Field::TITLE, title.length());
    title_ = title;
}

void Snippet::setCreated(QDateTime created)
{
    created_ = created;
}

void Snippet::setLang(QString lang)
{
    if (lang.length() > MAX_LANG_LEN)
        throw TooLongContentException(Field::LANG, lang.length());

    if (!availableLangs_.contains(lang))
        throw UnsupportedLanguageException(lang.toUtf8().constData()); // moze nie dzialac na windowsie

    lang_ = lang;
}

void Snippet::setContent(QString content)
{
    if (content.length() > MAX_CONTENT_LEN)
        throw TooLongContentException(Field::CONTENT, content.length());

    content_ = content;
}

QString Snippet::author() const
{
    return author_;
}

QString Snippet::title() const
{
    return title_;
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

    json_obj.insert(fieldToString(Field::AUTHOR), author());
    json_obj.insert(fieldToString(Field::TITLE), title());
    json_obj.insert(fieldToString(Field::CREATED), created().toSecsSinceEpoch());
    json_obj.insert(fieldToString(Field::LANG), lang());
    json_obj.insert(fieldToString(Field::CONTENT), content());

    return json_obj;
}

Snippet Snippet::fromJson(QJsonObject &obj)
{
    for (int field_int = Field::AUTHOR; field_int < Field::CONTENT; ++field_int)
    {
        if (!obj.contains(fieldToString(static_cast<Field>(field_int))) ||
            !obj.value(fieldToString(static_cast<Field>(field_int))).isString())
            throw InvalidSnippetJsonException();
    }

    QString author = obj.value(Snippet::fieldToString(Field::AUTHOR)).toString();
    QString title = obj.value(Snippet::fieldToString(Field::TITLE)).toString();
    QDateTime created = QDateTime::fromString(obj.value(Snippet::fieldToString(Field::CREATED)).toString());
    QString lang = obj.value(Snippet::fieldToString(Field::LANG)).toString();
    QString content = obj.value(Snippet::fieldToString(Field::CONTENT)).toString();

    Snippet snippet(author, title, created, lang, content);

    return snippet;
}

Snippet Snippet::fromJson(QJsonObject &&obj)
{
    return Snippet::fromJson(obj);
}

QString Snippet::fieldToString(Field field)
{
    return fieldToStringMap[field];
}

int Snippet::fieldToItsMaxLength(Field field)
{
    return fieldToItsMaxLengthMap[field];
}

const QHash<Snippet::Field, QString> Snippet::fieldToStringMap =
    {{Field::AUTHOR, QString("author")},
     {Field::TITLE, QString("title")},
     {Field::CREATED, QString("created")},
     {Field::LANG, QString("lang")},
     {Field::CONTENT, QString("content")}};

const QHash<Snippet::Field, int> Snippet::fieldToItsMaxLengthMap =
    {{Field::AUTHOR, MAX_AUTHOR_LEN},
     {Field::TITLE, MAX_TITLE_LEN},
     {Field::LANG, MAX_LANG_LEN},
     {Field::CONTENT, MAX_CONTENT_LEN}};

QStringList Snippet::availableLangs_ = {"c++", "python", "javascript"};

Snippet &Snippet::operator=(const Snippet &s)
{
    if (&s == this)
        return *this;
    
    setAuthor(s.author());
    setTitle(s.title());
    setCreated(s.created());
    setLang(s.lang());
    setContent(s.content());

    return *this;
}

bool Snippet::operator==(const Snippet &s)
{
    bool result = s.author() == author() && s.title() == title() && s.created() == created() && s.lang() == lang() && s.content() == content();
    return result;
}

QVariant Snippet::toVariant() const
{
    QVariant snippVariant;
    snippVariant.setValue(*this);
    return snippVariant;
}

QStringList Snippet::availableLangs()
{
    return availableLangs_;
}
