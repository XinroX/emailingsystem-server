#include <QCoreApplication>
#include <QDebug>
#include "serverservice.h"
#include "receiver.h"
#include "../emailingsystem-core/serializer.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IDbConnection* db = new DbConnection;
    ServerService service{nullptr, db};
    QVariantMap headerMap;
    headerMap["code"] = QString::number(static_cast<int>(MessageCode::GET_MESSAGES_RECEIVED));
    QVariantMap bodyMap;
    bodyMap["login"] = "test";
    QVariantMap map;
    map["header"] = headerMap;
    map["body"] = bodyMap;
    QJsonDocument doc = QJsonDocument::fromVariant(map);
    Receiver receiver;
    QObject::connect(&service, &ServerService::ready, &receiver, &Receiver::print);
    service.StartHandling(doc.toJson());


    //core::Message m{"123", "123", "123", "123"};
    return a.exec();
}
