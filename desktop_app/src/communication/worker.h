#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include <QByteArray>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

signals:

public slots:
    void get(QString query);
    void post(QString location, QByteArray data);

private slots:
    void readyRead();

private:
    QString const location_ = "127.0.0.1:8000/app";
    QNetworkAccessManager manager_;
};

#endif // WORKER_H
