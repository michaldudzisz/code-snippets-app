#ifndef SNIPPET_SEARCH_PATTERN
#define SNIPPET_SEARCH_PATTERN

#include <QObject>
#include <QString>
#include <QDateTime>

struct SnippetSearchPattern : QObject
{
    Q_OBJECT

public:

    SnippetSearchPattern() = default;
    SnippetSearchPattern(const SnippetSearchPattern & other) = default;
    SnippetSearchPattern &operator=(const SnippetSearchPattern &);
    ~SnippetSearchPattern() = default;

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
};

#endif