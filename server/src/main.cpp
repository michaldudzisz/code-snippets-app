#include <QCoreApplication>

#include "apihandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    ApiHandler req_handler;
    req_handler.run();

    return app.exec();
}