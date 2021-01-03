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
<<<<<<< HEAD
    QJsonArray response;
    SnippetSearchPattern match_pattern;
    QJsonDocument body;
    QList<Snippet> snippets;

    if (socket->readJson(body))
    {
=======
    qInfo() << "received get request";

    QJsonArray response; 
>>>>>>> b15aa22ab108a091e1901109803d554c16b78b01

        try 
        {
            if (!body.object().isEmpty())
                match_pattern = SnippetSearchPattern::fromJson(body.object());
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
    else
    {
        resendError(socket, "Invalid get request body - should be a json, even empty");
    }
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
