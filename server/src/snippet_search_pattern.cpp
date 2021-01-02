#include "snippet_search_pattern.h"
#include "snippet.h"
#include "too_long_content_exception.h"
#include "unsupported_language_exception.h"

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

    if (!Snippet::availableLangs().contains(lang))
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
