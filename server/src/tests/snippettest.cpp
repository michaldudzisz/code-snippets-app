#include <QString>
#include <QDateTime>

#include "snippettest.h"
#include "too_long_content_exception.h"
#include "unsupported_language_exception.h"

void SnippetTest::constructor()
{
    QDateTime prev_time = QDateTime::currentDateTime();
    Snippet s;
    QDateTime after_time = QDateTime::currentDateTime();

    QVERIFY(s.author() == "");
    QVERIFY(s.title() == "");
    QVERIFY(s.created() >= prev_time);
    QVERIFY(s.created() <= after_time);
    QVERIFY(s.lang() == "");
    QVERIFY(s.content() == "");
}

void SnippetTest::copyingConstructor()
{
    Snippet prev_snippet;
    prev_snippet.setAuthor("username");
    prev_snippet.setTitle("some title");
    prev_snippet.setLang("c++");
    prev_snippet.setContent("void main() {}");

    Snippet created_by_copying(prev_snippet);

    QVERIFY(created_by_copying.author() == prev_snippet.author());
    QVERIFY(created_by_copying.title() == prev_snippet.title());
    QVERIFY(created_by_copying.created() == prev_snippet.created());
    QVERIFY(created_by_copying.lang() == prev_snippet.lang());
    QVERIFY(created_by_copying.content() == prev_snippet.content());
}

void SnippetTest::noDateConstructor()
{
    QString author("username");
    QString title("some title");
    QString lang("c++");
    QDateTime prev_time = QDateTime::currentDateTime();
    Snippet s_without_content(author, title, lang);
    QDateTime after_time = QDateTime::currentDateTime();

    QVERIFY(s_without_content.author() == author);
    QVERIFY(s_without_content.title() == title);
    QVERIFY(s_without_content.created() >= prev_time);
    QVERIFY(s_without_content.created() <= after_time);
    QVERIFY(s_without_content.lang() == lang);
    QVERIFY(s_without_content.content() == "");

    QString content("some content");
    prev_time = QDateTime::currentDateTime();
    Snippet s_with_content(author, title, lang, content);
    after_time = QDateTime::currentDateTime();

    QVERIFY(s_with_content.author() == author);
    QVERIFY(s_with_content.title() == title);
    QVERIFY(s_with_content.created() >= prev_time);
    QVERIFY(s_with_content.created() <= after_time);
    QVERIFY(s_with_content.lang() == lang);
    QVERIFY(s_with_content.content() == content);

    int oversized_author_length = Snippet::MAX_AUTHOR_LEN + 1;
    author = QString(oversized_author_length, 'a');
    QVERIFY_EXCEPTION_THROWN(Snippet(author, title, lang, content),
                             TooLongContentException);

    author = QString("username");
    lang = QString("unsupported language");
    QVERIFY_EXCEPTION_THROWN(Snippet(author, title, lang, content),
                             UnsupportedLanguageException);
}

void SnippetTest::allMembersConstructor()
{
    QString author("username");
    QString title("some title");
    QDateTime time = QDateTime::currentDateTime();
    QString lang("c++");

    Snippet s(author, title, time, lang);
    QVERIFY(s.author() == "username");
    QVERIFY(s.title() == title);
    QVERIFY(s.created() == time);
    QVERIFY(s.lang() == "c++");
    QVERIFY(s.content() == "");

    QString content("void main() {}");
    s = Snippet(author, title, time, lang, content);
    QVERIFY(s.author() == "username");
    QVERIFY(s.created() == time);
    QVERIFY(s.lang() == "c++");
    QVERIFY(s.content() == content);

    int oversized_author_length = Snippet::MAX_AUTHOR_LEN + 1;
    author = QString(oversized_author_length, 'a');
    QVERIFY_EXCEPTION_THROWN(Snippet(author, title, time, lang, content),
                             TooLongContentException);
}

void SnippetTest::assignmentOperator()
{
    QString previous_username("prev_username");
    QString previous_title("previous title");
    QString previous_lang("c++");
    QString previous_content("previous content");
    Snippet prev(previous_username, previous_title, QDateTime::currentDateTime(),
                 previous_lang, previous_content);

    QString new_username("new_username");
    QString new_title("new title");
    QString new_lang("python");
    QString new_content("new content");
    QDateTime new_time = QDateTime::currentDateTime();
    Snippet next(new_username, new_title, new_time, new_lang, new_content);

    prev = next;

    QVERIFY(prev.author() == new_username);
    QVERIFY(prev.title() == new_title);
    QVERIFY(prev.created() == new_time);
    QVERIFY(prev.lang() == new_lang);
    QVERIFY(prev.content() == new_content);
}

void SnippetTest::toJson() const
{
    QJsonObject json_obj;
    json_obj.insert("author", "username");
    json_obj.insert("title", "some title");
    QDateTime time = QDateTime::currentDateTime();
    json_obj.insert("created", time.toString());
    json_obj.insert("lang", "c++");
    json_obj.insert("content", "void main() {}");

    Snippet s("username", "some title", time, "c++", "void main() {}");

    QVERIFY(json_obj == s.toJson());
}

void SnippetTest::fromJson()
{
    QString author("username");
    QString title("some title");
    // QDateTime traci na dokladnosci przy parsowaniu, dlatego parsuje od razu:
    QDateTime created = QDateTime::fromString(QDateTime::currentDateTime().toString());
    QString lang("c++");
    QString content("void main() {}");

    QJsonObject json_obj;
    json_obj.insert("author", author);
    json_obj.insert("title", title);
    json_obj.insert("created", created.toString());
    json_obj.insert("lang", lang);
    json_obj.insert("content", content);

    Snippet s = Snippet::fromJson(json_obj);
    QVERIFY(s.author() == author);
    QVERIFY(s.title() == title);
    QVERIFY(s.created() == created);
    QVERIFY(s.lang() == lang);
    QVERIFY(s.content() == content);
}

void SnippetTest::fromJsonRValueArg()
{
    QString author("username");
    QString title("some title");
    // QDateTime traci na dokladnosci przy parsowaniu, dlatego parsuje od razu:
    QDateTime created = QDateTime::fromString(QDateTime::currentDateTime().toString());
    QString lang("c++");
    QString content("void main() {}");

    QJsonObject json_obj;
    json_obj.insert("author", author);
    json_obj.insert("title", title);
    json_obj.insert("created", created.toString());
    json_obj.insert("lang", lang);
    json_obj.insert("content", content);

    QJsonDocument tmp_document(json_obj);
    Snippet s = Snippet::fromJson(tmp_document.object());

    QVERIFY(s.author() == author);
    QVERIFY(s.title() == title);
    QVERIFY(s.created() == created);
    QVERIFY(s.lang() == lang);
    QVERIFY(s.content() == content);
}

void SnippetTest::setAuthor()
{
    Snippet s;
    QString author("username");

    s.setAuthor(author);
    QVERIFY(s.author() == author);

    int author_length = Snippet::MAX_AUTHOR_LEN + 1;
    QString oversized_author(author_length, 'a');
    QVERIFY_EXCEPTION_THROWN(s.setAuthor(oversized_author), TooLongContentException);
}

void SnippetTest::setTitle()
{
    Snippet s;
    QString title("some title");

    s.setTitle(title);
    QVERIFY(s.title() == title);

    int title_length = Snippet::MAX_TITLE_LEN + 1;
    QString oversized_title(title_length, 'a');
    QVERIFY_EXCEPTION_THROWN(s.setTitle(oversized_title), TooLongContentException);
}

void SnippetTest::setCreated()
{
    Snippet s;
    QDateTime time = QDateTime::currentDateTime();

    s.setCreated(time);
    QVERIFY(s.created() == time);
}

void SnippetTest::setLang()
{
    Snippet s;
    QString lang("c++");

    s.setLang(lang);
    QVERIFY(s.lang() == lang);

    QString unsupported_lang("unsupported lang");
    QVERIFY_EXCEPTION_THROWN(s.setLang(unsupported_lang), UnsupportedLanguageException);

    int oversized_lang_size = Snippet::MAX_LANG_LEN + 1;
    QString oversized_lang(oversized_lang_size, 'a');
    QVERIFY_EXCEPTION_THROWN(s.setLang(oversized_lang), TooLongContentException);
}

void SnippetTest::setContent()
{
    Snippet s;
    QString content("void main() {}");

    s.setContent(content);
    QVERIFY(s.content() == content);

    int oversized_content_size = Snippet::MAX_CONTENT_LEN + 1;
    QString oversized_content(oversized_content_size, 'a');
    QVERIFY_EXCEPTION_THROWN(s.setContent(oversized_content), TooLongContentException);
}

void SnippetTest::author() const
{
    Snippet s;
    QString author("username");
    s.setAuthor(author);
    QVERIFY(s.author() == author);
}

void SnippetTest::title() const
{
    Snippet s;
    QString title("some title");
    s.setTitle(title);
    QVERIFY(s.title() == title);
}

void SnippetTest::created() const
{
    Snippet s;
    QDateTime created = QDateTime::currentDateTime();
    s.setCreated(created);
    QVERIFY(s.created() == created);
}

void SnippetTest::lang() const
{
    Snippet s;
    QString lang("c++");
    s.setLang(lang);
    QVERIFY(s.lang() == lang);
}

void SnippetTest::content() const
{
    Snippet s;
    QString lang("c++");
    s.setLang(lang);
    QVERIFY(s.lang() == lang);
}

void SnippetTest::fieldToString()
{
    QVERIFY(Snippet::fieldToString(Snippet::Field::AUTHOR) == "author");
    QVERIFY(Snippet::fieldToString(Snippet::Field::TITLE) == "title");
    QVERIFY(Snippet::fieldToString(Snippet::Field::CREATED) == "created");
    QVERIFY(Snippet::fieldToString(Snippet::Field::LANG) == "lang");
    QVERIFY(Snippet::fieldToString(Snippet::Field::CONTENT) == "content");
}

void SnippetTest::fieldToItsMaxLength()
{
    QVERIFY(Snippet::fieldToItsMaxLength(Snippet::Field::AUTHOR) == Snippet::MAX_AUTHOR_LEN);
    QVERIFY(Snippet::fieldToItsMaxLength(Snippet::Field::TITLE) == Snippet::MAX_TITLE_LEN);
    QVERIFY(Snippet::fieldToItsMaxLength(Snippet::Field::LANG) == Snippet::MAX_LANG_LEN);
    QVERIFY(Snippet::fieldToItsMaxLength(Snippet::Field::CONTENT) == Snippet::MAX_CONTENT_LEN);
}