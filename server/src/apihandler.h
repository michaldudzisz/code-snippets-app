#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <exception>

#include <QObject>
#include <QString>
#include <QHash>
#include <QStack>
#include <QSharedPointer>

#include "qhttpengine/socket.h"
#include "qhttpengine/server.h"
#include "qhttpengine/qobjecthandler.h"

#include "snippet.h"
#include "snippet_repository_interface.h"

/** @brief Responsible for mapping REST API requests and handling them as API controller.
 * Allows using POST requests with JSON body and GET with path variables.
 */ 

class ApiHandler : public QObject
{

    Q_OBJECT

public:
    /** Creates default ApiHandler object. */
    ApiHandler();

    /** Runs server. May be called right after creating ApiHandler object with non-parameter constructor. */
    void run();

public slots:
    void handleRequest(QHttpEngine::Socket *socket);

protected:
    QHttpEngine::QObjectHandler handler_;
    QHttpEngine::Server server_;

    void handleGetRequest(QHttpEngine::Socket *socket);
    void handlePostRequest(QHttpEngine::Socket *socket);

    void registerSnippet(Snippet &s);
    void respondWithJsonArray(QHttpEngine::Socket * socket, const QJsonArray &array);

    void resendError(QHttpEngine::Socket * socket, const char * info);
    void resendError(QHttpEngine::Socket * socket, std::exception &e);

    QSharedPointer<SnippetRepositoryInterface> repository_;

    QHash<QHttpEngine::Socket::Method,
          std::function<void(ApiHandler &, QHttpEngine::Socket *)>>
        requestHandlers_ = {{QHttpEngine::Socket::Method::GET,
                            &ApiHandler::handleGetRequest},
                           {QHttpEngine::Socket::Method::POST,
                            &ApiHandler::handlePostRequest}};

    QStack<Snippet> snippets_;
    const qint16 PORT_NUMBER = 8000;
};

#endif
