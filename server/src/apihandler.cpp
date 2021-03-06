#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QDebug>

#include <string>
#include <iostream>
#include <cstdio>

#include "apihandler.h"
#include "snippet.h"
#include "too_long_content_exception.h"
#include "invalid_snippet_json_exception.h"
#include "database_error_exception.h"
#include "snippet_repository_concrete.h"

ApiHandler::ApiHandler()
{
    handler_.registerMethod("app", this, &ApiHandler::handleRequest);
    server_.setHandler(&handler_);
    repository_ = SnippetRepositoryConcrete::getInstance();
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
    server_.listen(QHostAddress::LocalHost, PORT_NUMBER);
}

void ApiHandler::registerSnippet(Snippet &snippet)
{
    try
    {
        repository_->saveSnippet(snippet);
    }
    catch (std::exception &e)
    {
        // TODO jakis log z bledem, a dla klienta:
        throw DatabaseErrorException("Unable to save snippet due to servers problem.");
    }
}

void ApiHandler::handleGetRequest(QHttpEngine::Socket *socket)
{
    QJsonArray response;
    QJsonDocument body;
    QList<Snippet> snippets;
    SnippetSearchPattern match_pattern;

    qInfo() << "received get request";

    QHttpEngine::Socket::QueryStringMap query_string = socket -> queryString();

    try 
    {
        match_pattern = SnippetSearchPattern::fromQueryString(query_string);
        snippets = repository_->pullSnippets(match_pattern);
    }
    catch (std::exception &e)
    {
        resendError(socket, e);
        return;
    }

    for (Snippet snipp : snippets)
        response.append(snipp.toJson());

    respondWithJsonArray(socket, response);
}

void ApiHandler::handlePostRequest(QHttpEngine::Socket *socket)
{
    qInfo() << "received post request";

    QJsonDocument body;
    if (socket->readJson(body))
    {
        try
        {
            Snippet posted = Snippet::fromJson(body.object());
            registerSnippet(posted);
        }
        catch (std::exception &e)
        {
            resendError(socket, e);
            return;
        }

        socket->setStatusCode(QHttpEngine::Socket::OK);
        socket->writeHeaders();
        socket->close();
    }
}

void ApiHandler::resendError(QHttpEngine::Socket *socket, std::exception &e)
{
    resendError(socket, e.what());
}

void ApiHandler::resendError(QHttpEngine::Socket *socket, const char *info)
{
    QJsonObject response;
    response["message"] = info;
    socket->setStatusCode(QHttpEngine::Socket::BadRequest);
    socket->setHeader("Content-Type", "json");
    socket->writeHeaders();
    socket->writeJson(QJsonDocument(response));
}

void ApiHandler::respondWithJsonArray(QHttpEngine::Socket *socket, const QJsonArray &array)
{
    socket->setStatusCode(QHttpEngine::Socket::OK);
    socket->setHeader("Content-Type", "json");
    socket->writeHeaders();
    socket->writeJson(QJsonDocument(array));
}
