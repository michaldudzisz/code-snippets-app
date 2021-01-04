#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <../server/src/snippet.h>


class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

signals:
    void data_received(QByteArray& byte_array);

public slots:
    void get(QString& title, QString& lang, QString& author, QDateTime& date_from, QDateTime& date_to);
    void post(Snippet& snip);

private slots:
    void readyRead();

private:
    QString const LOCATION_ = "http://127.0.0.1:8000/app";
    QNetworkAccessManager manager_;
};

#endif // WORKER_H
