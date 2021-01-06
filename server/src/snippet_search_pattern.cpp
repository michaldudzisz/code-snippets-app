#include <limits>

#include <QDebug>

#include "snippet_search_pattern.h"
#include "snippet.h"
#include "too_long_content_exception.h"
#include "unsupported_language_exception.h"
#include "invalid_get_request_body_exception.h"

const QString SnippetSearchPattern::SQLITE_SEQ_CHAR = "%";

const QString SnippetSearchPattern::AUTHOR_JSON_FIELD = "author_subsequence";
const QString SnippetSearchPattern::TITLE_JSON_FIELD = "title_subsequence";
const QString SnippetSearchPattern::CREATED_FROM_JSON_FIELD = "created_from";
const QString SnippetSearchPattern::CREATED_TO_JSON_FIELD = "created_to";
const QString SnippetSearchPattern::LANG_JSON_FIELD = "lang";

SnippetSearchPattern::SnippetSearchPattern() {}

SnippetSearchPattern::SnippetSearchPattern(const SnippetSearchPattern &other)
{
    setAuthorSubsequence(other.authorSubsequence());
    setTitleSubsequence(other.titleSubsequence());
    setCreatedFrom(other.createdFrom());
    setCreatedTo(other.createdTo());
    setLang(other.lang());
}

SnippetSearchPattern &SnippetSearchPattern::operator=(const SnippetSearchPattern &other)
{
    if (&other == this)
        return *this;

    setAuthorSubsequence(other.authorSubsequence());
    setTitleSubsequence(other.titleSubsequence());
    setCreatedFrom(other.createdFrom());
    setCreatedTo(other.createdTo());
    setLang(other.lang());

    return *this;
}

void SnippetSearchPattern::setAuthorSubsequence(const QString &author)
{
    if (author.length() > Snippet::MAX_AUTHOR_LEN)
        throw TooLongContentException(Snippet::Field::AUTHOR, author.length());
    authorSubsequence_ = author;
}

void SnippetSearchPattern::setTitleSubsequence(const QString &title)
{
    if (title.length() > Snippet::MAX_TITLE_LEN)
        throw TooLongContentException(Snippet::Field::TITLE, title.length());
    titleSubsequence_ = title;
}

void SnippetSearchPattern::setCreatedFrom(const QDateTime &from)
{
    createdFrom_ = from;
}

void SnippetSearchPattern::setCreatedTo(const QDateTime &to)
{
    createdTo_ = to;
}

void SnippetSearchPattern::setLang(const QString &lang)
{
    if (lang.length() > Snippet::MAX_LANG_LEN)
        throw TooLongContentException(Snippet::Field::LANG, lang.length());

    if (!Snippet::availableLangs().contains(lang) && !lang.isEmpty())
        throw UnsupportedLanguageException(lang.toUtf8().constData()); // moze nie dzialac na windowsie

    lang_ = lang;
}

QString SnippetSearchPattern::authorSubsequence() const
{
    return authorSubsequence_;
}

QString SnippetSearchPattern::titleSubsequence() const
{
    return titleSubsequence_;
}

QDateTime SnippetSearchPattern::createdFrom() const
{
    return createdFrom_;
}

QDateTime SnippetSearchPattern::createdTo() const
{
    return createdTo_;
}

QString SnippetSearchPattern::lang() const
{
    return lang_;
}

QString SnippetSearchPattern::authorSQLiteSubsequence() const
{
    return QString(SQLITE_SEQ_CHAR + authorSubsequence() + SQLITE_SEQ_CHAR);
}

QString SnippetSearchPattern::titleSQLiteSubsequence() const
{
    return QString(SQLITE_SEQ_CHAR + titleSubsequence() + SQLITE_SEQ_CHAR);
}

QString SnippetSearchPattern::languageSQLite() const
{
    if (lang().isEmpty())
        return QString(SQLITE_SEQ_CHAR);
    else
        return lang();
}

bool SnippetSearchPattern::isEmpty() const
{
    bool result;
    result = authorSubsequence().isEmpty() && titleSubsequence().isEmpty() && lang().isEmpty();
    result = result && createdFrom().isNull() && createdTo().isNull();
    return result;
}

qint64 SnippetSearchPattern::createdFromSQLite() const
{
    if (createdFrom().isNull())
        return std::numeric_limits<qint64>::min();
    else
        return createdFrom().toSecsSinceEpoch();
}

qint64 SnippetSearchPattern::createdToSQLite() const
{
    if (createdTo().isNull())
        return std::numeric_limits<qint64>::max();
    else
        return createdTo().toSecsSinceEpoch();
}

SnippetSearchPattern SnippetSearchPattern::fromJson(QJsonObject &json_obj)
{
    validateJson(json_obj);

    QString author_subsequence = json_obj.value(AUTHOR_JSON_FIELD).toString();
    QString title_subsequence = json_obj.value(TITLE_JSON_FIELD).toString();
    QString lang = json_obj.value(LANG_JSON_FIELD).toString();

    QDateTime created_from = parseDateTime(json_obj.value(CREATED_FROM_JSON_FIELD));
    QDateTime created_to = parseDateTime(json_obj.value(CREATED_TO_JSON_FIELD));

    SnippetSearchPattern pattern;
    pattern.setAuthorSubsequence(author_subsequence);
    pattern.setTitleSubsequence(title_subsequence);
    pattern.setCreatedFrom(created_from);
    pattern.setCreatedTo(created_to);
    pattern.setLang(lang);

    return pattern;
}

QJsonObject SnippetSearchPattern::toJson() const
{
    QJsonObject json_obj;
    json_obj.insert(AUTHOR_JSON_FIELD, authorSubsequence());
    json_obj.insert(TITLE_JSON_FIELD, titleSubsequence());
    json_obj.insert(LANG_JSON_FIELD, lang());

    json_obj.insert(CREATED_FROM_JSON_FIELD, dateToJsonValue(createdFrom()));
    json_obj.insert(CREATED_TO_JSON_FIELD, dateToJsonValue(createdTo()));

    return json_obj;
}

void SnippetSearchPattern::validateJson(const QJsonObject &obj)
{
    bool isValid = true;
    isValid = isValid && obj.contains(AUTHOR_JSON_FIELD) &&
              obj.value(AUTHOR_JSON_FIELD).isString();
    isValid = isValid && obj.contains(TITLE_JSON_FIELD) &&
              obj.value(TITLE_JSON_FIELD).isString();
    isValid = isValid && obj.contains(CREATED_FROM_JSON_FIELD) &&
              (obj.value(CREATED_FROM_JSON_FIELD).isDouble() ||
               obj.value(CREATED_FROM_JSON_FIELD).isNull());
    isValid = isValid && obj.contains(CREATED_TO_JSON_FIELD) &&
              (obj.value(CREATED_TO_JSON_FIELD).isDouble() ||
               obj.value(CREATED_TO_JSON_FIELD).isNull());
    isValid = isValid && obj.contains(LANG_JSON_FIELD) &&
              obj.value(LANG_JSON_FIELD).isString();

    if (!isValid)
        throw InvalidGetRequestBodyException();
}

QDateTime SnippetSearchPattern::parseDateTime(const QJsonValue &val)
{
    if (val.isNull())
        return QDateTime();

    QVariant val_maybe = val.toVariant();
    bool readCorrectly = false;
    qint64 secSinceEpoch = val_maybe.toLongLong(&readCorrectly);

    if (!readCorrectly)
        throw InvalidGetRequestBodyException();

    return QDateTime::fromSecsSinceEpoch(secSinceEpoch);
}

QDateTime SnippetSearchPattern::parseDateTime(const QJsonValue &&val)
{
    return parseDateTime(val);
}

SnippetSearchPattern SnippetSearchPattern::fromJson(QJsonObject &&obj)
{
    return fromJson(obj);
}

QJsonValue SnippetSearchPattern::dateToJsonValue(const QDateTime &date)
{
    QJsonValue json_val;
    if (date.isValid())
        json_val = date.toSecsSinceEpoch();
    else
        json_val = QJsonValue::Null;

    return json_val;
}

SnippetSearchPattern SnippetSearchPattern::fromQueryString(const QueryStringMap &query)
{
    SnippetSearchPattern pattern;

    if (query.isEmpty())
        return pattern;

    if (query.contains(AUTHOR_JSON_FIELD))
        pattern.setAuthorSubsequence(query.value(AUTHOR_JSON_FIELD));
    if (query.contains(TITLE_JSON_FIELD))
        pattern.setTitleSubsequence(query.value(TITLE_JSON_FIELD));
    if (query.contains(LANG_JSON_FIELD))
        pattern.setLang(query.value(LANG_JSON_FIELD));

    if (query.contains(CREATED_FROM_JSON_FIELD) && !query.value(CREATED_FROM_JSON_FIELD).isEmpty())
    {
        QString value = query.value(CREATED_FROM_JSON_FIELD);
        pattern.setCreatedFrom(queryStringToDateTime(value));
    }
    if (query.contains(CREATED_TO_JSON_FIELD) && !query.value(CREATED_TO_JSON_FIELD).isEmpty())
    {
        QString value = query.value(CREATED_TO_JSON_FIELD);
        pattern.setCreatedTo(queryStringToDateTime(value));
    }

    return pattern;
}

QDateTime SnippetSearchPattern::queryStringToDateTime(const QString &query)
{
    bool read_correctly = false;
    qint64 date_time = query.toLongLong(&read_correctly);
    if (!read_correctly)
        throw InvalidGetRequestBodyException();
    return QDateTime::fromSecsSinceEpoch(date_time);
}

QDateTime SnippetSearchPattern::queryStringToDateTime(const QString &&query)
{
    return queryStringToDateTime(query);
}
