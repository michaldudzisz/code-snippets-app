#include "worker.h"
#include <QUrl>

Worker::Worker(QObject *parent) : QObject(parent)
{

}

void Worker::get(QString location)
{
    qInfo() << "getting from server";
    QNetworkReply* reply = manager_.get(QNetworkRequest(QUrl(location)));
    connect(reply, &QNetworkReply::readyRead, this, &Worker::readyRead);
}

void Worker::post(QString location, QByteArray data)
{
    // niedokonczone
    qInfo() << "posting the msg";
    QNetworkRequest request = QNetworkRequest(QUrl(location));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "json");
    QNetworkReply* reply = manager_.post(request, data);
    connect(reply, &QNetworkReply::readyRead, this, &Worker::readyRead);
}

void Worker::readyRead()
{
    qInfo() << "got answer";
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if (reply) qInfo() << reply->readAll();
    else qInfo() << "no reply??";
}

