#include <QCoreApplication>
#include <QDebug>
#include "serverservice.h"
#include "receiver.h"
#include "../emailingsystem-core/serializer.h"
#include "Server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    quint16 port = 3333;
    if (!server.listen(QHostAddress::Any, port)) {
        qCritical() << "Error: " << server.errorString();
    }

    //core::Message m{"123", "123", "123", "123"};
    return a.exec();
}
