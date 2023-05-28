#ifndef SERVERSERVICE_H
#define SERVERSERVICE_H

#include <QObject>
#include "../emailingsystem-core/messagebuilder.h"
#include "dbconnection.h"


enum class MessageCode {
    LOGIN_REQUEST = 0,
    LOGIN_REJECT = 11,
    LOGIN_ACCEPT = 12,
    LOGIN_ERROR = 13,
    GET_MESSAGES_RECEIVED = 21,
    GET_NEW_MESSAGES_RECEIVED = 22,
    GET_MESSAGES_SENT = 23,
    NO_MESSAGE_FOUND = 31,
    MESSAGES_FOUND = 32
};

class ServerService : public QObject
{
    Q_OBJECT
public:
    explicit ServerService(QObject *parent = nullptr, IDbConnection* db = nullptr);

    void StartHandling(const QByteArray& message);

signals:
    void userLogin();
    void ready(const QByteArray& message);
    void errorOccured(const QString& errorMessage);
private:
    void processHeader();
    void processLoginRequest();
    void processGetReceivedMessagesRequest();
    //void prepareLoginResponse(const QString& content);



    QByteArray message;
    IDbConnection* db;
};

#endif // SERVERSERVICE_H
