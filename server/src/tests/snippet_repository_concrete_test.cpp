#include "snippet_repository_concrete_test.h"
#include <cstdio>
#include <QDebug>

void SnippetRepositoryConcreteTest::initTestCase()
{
    repository_ = SnippetRepositoryConcrete::getInstance();
    itnitTestTime_ = QDateTime::currentDateTime();
}

Snippet SnippetRepositoryConcreteTest::createExampleSnippet()
{
    Snippet s;
    s.setAuthor("username");
    s.setTitle("some title");
    s.setCreated(QDateTime::currentDateTime());
    s.setLang("c++");
    s.setContent("void main() {}");

    return s;
}


void SnippetRepositoryConcreteTest::saveSnippet()
{
    QFETCH_GLOBAL(Snippet, snippets);

    auto performSave = [this](Snippet s) {
        repository_->saveSnippet(s);
        return true;
    };

    QVERIFY(performSave(snippets));
}

void SnippetRepositoryConcreteTest::pullSnippetsNoArg() 
{
    QFETCH_GLOBAL(Snippet, snippets);
    QList<Snippet> snipps = repository_ -> pullSnippets();
    QVERIFY(snipps.contains(snippets));
}

void SnippetRepositoryConcreteTest::pullSnippetsByAuthorAndTitle() 
{
    QFETCH_GLOBAL(Snippet, snippets);

    SnippetSearchPattern pattern;

    QString author_subsequence  = snippets.author();
    author_subsequence.truncate(3);
    pattern.setAuthorSubsequence(author_subsequence);

    QString title_subsequence  = snippets.title();
    title_subsequence.truncate(3);
    pattern.setTitleSubsequence(title_subsequence);
    
    QList<Snippet> snipps_from_db = repository_ -> pullSnippets(pattern);
    QVERIFY(snipps_from_db.contains(snippets));
}



/*
void SnippetRepositoryConcreteTest::pullSnippets()
{
    Snippet snippet = createExampleSnippet();

    QList<Snippet> snippets = repository_->pullSnippets();
}

void SnippetRepositoryConcreteTest::pullSnippetsByAuthorAndTitle()
{
    SnippetSearchPattern pattern;
    pattern.setLang("c++");
    QList<Snippet> snippets = repository_->pullSnippets(pattern);

    pattern.setAuthorSubsequence("rnam"); // use rnam e
    snippets = repository_->pullSnippets(pattern);

    pattern.setTitleSubsequence("some"); // some title
    snippets = repository_->pullSnippets(pattern);
}
*/

void SnippetRepositoryConcreteTest::initTestCase_data()
{
    QTest::addColumn<Snippet>("snippets");

    Snippet snipp;

    snipp.setAuthor("michal");
    snipp.setTitle("c plus plus title");
    snipp.setCreated(itnitTestTime_);
    snipp.setLang("c++");
    snipp.setContent("void main() {}");
    QTest::newRow("c++1") << snipp;

    snipp.setAuthor("anna");
    snipp.setTitle("javascript title");
    snipp.setCreated(itnitTestTime_);
    snipp.setLang("javascript");
    snipp.setContent("console.log();");
    QTest::newRow("javascript1") << snipp;

    snipp.setAuthor("piotr");
    snipp.setTitle("python title");
    snipp.setCreated(itnitTestTime_);
    snipp.setLang("python");
    snipp.setContent("print(a)");
    QTest::newRow("python1") << snipp;

    QDateTime later = QDateTime::fromSecsSinceEpoch(itnitTestTime_.toSecsSinceEpoch() + 2);

    snipp.setAuthor("anna");
    snipp.setTitle("c plus plus title");
    snipp.setCreated(later);
    snipp.setLang("c++");
    snipp.setContent("void main() {}");
    QTest::newRow("c++2") << snipp;

    snipp.setAuthor("piotr");
    snipp.setTitle("javascript title");
    snipp.setCreated(later);
    snipp.setLang("javascript");
    snipp.setContent("console.log();");
    QTest::newRow("javascript2") << snipp;

}