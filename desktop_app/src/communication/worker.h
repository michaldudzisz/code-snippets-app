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
#include <QHash>
#include <../server/src/snippet.h>

/** @brief Responsible for sending requests and receving data
 *  Allows using get and post messages. 
 *  Address is defined by private field LOCATION_;
 */

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

signals:

    /** Signal emited when data from server is received and ready to send to MainWindow object
     * @param byte_array data to send to MainWindow object
     */
    void data_received(QByteArray& byte_array);

    /** Signal emitted when server responds with message of status code other than 200
     * @param status_code error's code
     */
    void communication_error(int status_code);

public slots:
    /** Method allowing sending get request. Request is created basing on given argument.
     * @param hash_map map with possible following keys: author_subsequence,
     * title_subsequence, author_subsequence, created_from, created_to.
     * Map does not need to contain all the possible keys
     */
    void get(QHash<QString, QString>& hash_map);

    /** Method allowing sending post request. Request is created basing on given argument.
     * @param snip an object containing all information about data to be sent.
     */
    void post(Snippet& snip);

private slots:
    void readyRead();

private:
    QString const LOCATION_ = "http://127.0.0.1:8000/app";
    QNetworkAccessManager manager_;
};

#endif // WORKER_H
