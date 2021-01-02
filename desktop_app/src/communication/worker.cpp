#include "worker.h"
#include <QUrl>
#include "../presenter/mainwindow.h"


Worker::Worker(QObject *parent) : QObject(parent)
{

}

void Worker::get(QString& title, QString& lang)
{
    qInfo() << "getting from server";
    QNetworkReply* reply = manager_.get(QNetworkRequest(QUrl(LOCATION_)));
    connect(reply, &QNetworkReply::readyRead, this, &Worker::readyRead);
}

void Worker::post(Snippet& snip)
{
    qInfo() << "posting the msg";
    QNetworkRequest request = QNetworkRequest(QUrl(LOCATION_));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "json");

    QJsonObject json_data = snip.toJson();
    QByteArray data = QJsonDocument(json_data).toJson();
    // worker_.post("http://127.0.0.1:8000/app", QJsonDocument(data).toJson());

    QNetworkReply* reply = manager_.post(request, data);
    connect(reply, &QNetworkReply::readyRead, this, &Worker::readyRead);
}

void Worker::readyRead()
{
    qInfo() << "got answer";
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    emit data_received();

    if (reply) qInfo() << reply->readAll();
    else qInfo() << "no reply??";
}

