#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QStack>

#include "qhttpengine/socket.h"
#include "qhttpengine/server.h"
#include "qhttpengine/qobjecthandler.h"

#include "snippet.h"

class ApiHandler : public QObject
{

    Q_OBJECT

public:
    ApiHandler();

    void run();
    void registerSnippet(Snippet &s);

public slots:
    void handleRequest(QHttpEngine::Socket *socket);

protected:
    QHttpEngine::QObjectHandler handler_;
    QHttpEngine::Server server_;

    void handleGetRequest(QHttpEngine::Socket *);
    void handlePostRequest(QHttpEngine::Socket *);

    QHash<QHttpEngine::Socket::Method,
          std::function<void(ApiHandler &, QHttpEngine::Socket *)>>
        requestHandlers_ = {{QHttpEngine::Socket::Method::GET,
                            &ApiHandler::handleGetRequest},
                           {QHttpEngine::Socket::Method::POST,
                            &ApiHandler::handlePostRequest}};

    QStack<Snippet> snippets_;
};

#endif
