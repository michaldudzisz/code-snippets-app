#include <QtTest/QtTest>
#include <QString>
#include <QDateTime>

#include "snippet.h"

class SnippetTest : public QObject
{
    Q_OBJECT
private slots:
    void constructor();
    void copyingConstructor();
    void noDateConstructor();
    void allMembersConstructor();

    void assignmentOperator();

    void toJson() const;
    void fromJson();
    void fromJsonRValueArg();

    void setAuthor();
    void setTitle();
    void setCreated();
    void setLang();
    void setContent();

    void author() const;
    void title() const;
    void created() const;
    void lang() const;
    void content() const;

    void fieldToString();
    void fieldToItsMaxLength();
};