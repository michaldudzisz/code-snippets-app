#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>

#include <string>
#include <iostream>

#include "apihandler.h"
#include "snippet.h"
#include "too_long_content_exception.h"
#include "invalid_snippet_json_exception.h"

// zrobic cos, zeby linkowana biblioteka automatycznie
// dodowala sie do zmiennej systemowej (qmake?)
// o to:
// LD_LIBRARY_PATH=$LD_LIBRARY_PATH://home/mdudzisz/zpr/cpp-server-test/lib
// export LD_LIBRARY_PATH

ApiHandler::ApiHandler()
{
    handler_.registerMethod("app", this, &ApiHandler::handleRequest);
    server_.setHandler(&handler_);
}

void ApiHandler::handleRequest(QHttpEngine::Socket *socket)
{
    if (requestHandlers_[socket->method()])
    {
        requestHandlers_[socket->method()](*this, socket);
    }
    else
    {
        socket->setStatusCode(QHttpEngine::Socket::BadRequest);
        socket->close();
    }
}

void ApiHandler::run()
{
    server_.listen(QHostAddress::LocalHost, 8000);
}

void ApiHandler::registerSnippet(Snippet &s)
{
    if (snippets_.size() > 4)
        snippets_.removeFirst();

    snippets_.push(s);
}

void ApiHandler::handleGetRequest(QHttpEngine::Socket *socket)
{
    QJsonArray response; 
    QJsonObject date_test = Snippet("michal", "c++", "int main() { return 0; }").toJson();
    response.push_back(date_test);

    for (int i = 0; i < snippets_.length(); ++i)
        response.push_back(snippets_[i].toJson());


    socket->setStatusCode(QHttpEngine::Socket::OK);
    socket->setHeader("Content-Type", "json");
    socket->writeHeaders();
    socket->writeJson(QJsonDocument(response));
}

void ApiHandler::handlePostRequest(QHttpEngine::Socket *socket)
{
    QJsonDocument body;
    if (socket->readJson(body))
    {
        try
        {
            Snippet posted = Snippet::fromJson(body.object());
            registerSnippet(posted);
            socket->setStatusCode(QHttpEngine::Socket::OK);
            socket->writeHeaders();
        }
        catch (std::exception &e)
        {
            QJsonObject response;
            response["message"] = e.what();
            socket->setStatusCode(QHttpEngine::Socket::BadRequest);
            socket->setHeader("Content-Type", "json");
            socket->writeHeaders();
            socket->writeJson(QJsonDocument(response));
        }
        socket->close();
    }
}
