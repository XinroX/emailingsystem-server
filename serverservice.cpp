#include "serverservice.h"
#include <QJsonDocument>
#include <QVariant>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QSharedPointer>
#include <QSqlQuery>


ServerService::ServerService(QObject *parent, IDbConnection* db)
    : QObject{parent}
{
    this->db = db;
}
    
void ServerService::StartHandling(const QByteArray& message) {
    this->message = message;
    processHeader();
}

void ServerService::processHeader() {
    QJsonDocument document = QJsonDocument::fromJson(message);
    qInfo() << document;
    QJsonObject obj = document["header"].toObject();
    
    MessageCode code = static_cast<MessageCode>(obj["code"].toString().toInt());
    
    qInfo() << static_cast<int>(code);
    
    switch (code) {
    case MessageCode::LOGIN_REQUEST:
        processLoginRequest();
        break;
    case MessageCode::GET_MESSAGES_RECEIVED:
        processGetReceivedMessagesRequest();
        break;
    case MessageCode::GET_MESSAGES_SENT:
        processGetSentMessagesRequest();
    }
}

void ServerService::processLoginRequest() {
    QJsonDocument document = QJsonDocument::fromJson(message);
    QString login, password;
    QJsonObject loginObject = document["body"].toObject();
    login = loginObject["login"].toString();
    password = loginObject["password"].toString();
    
    db->Connect();
    QSqlQuery query = db->GenerateQuery();
    query.prepare("SELECT id FROM users WHERE login=:login AND password=md5(:password)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    int suc = db->ProcessQuery(query);
    db->Disconnect();
    
    
    QByteArray loginResponse;
    QVariantMap map;
    if (suc == 0) map["code"] = QString::number(static_cast<int>(MessageCode::LOGIN_REJECT));
    else if (suc == 1) map["code"] = QString::number(static_cast<int>(MessageCode::LOGIN_ACCEPT));
    else map["code"] = QString::number(static_cast<int>(MessageCode::LOGIN_ERROR));
    QJsonObject obj = QJsonObject::fromVariantMap(map);
    QVariantMap headerMap;
    headerMap["header"] = map;
    document = QJsonDocument::fromVariant(headerMap);
    loginResponse = document.toJson();
    emit ready(loginResponse);
}

void ServerService::processGetReceivedMessagesRequest() {
    QJsonDocument document = QJsonDocument::fromJson(message);
    QJsonObject bodyObj = document["body"].toObject();
    QString login = bodyObj["login"].toString();
    
    db->Connect();
    QSqlQuery query = db->GenerateQuery();
    query.prepare("SELECT * FROM messages_by_login WHERE receiver_login=:login");
    query.bindValue(":login", login);
    int rows = db->ProcessQuery(query);
    db->Disconnect();
    
    QByteArray response;
    QVariantMap headerMap;
    if (rows == 0) {
        headerMap["code"] = QString::number(static_cast<int>(MessageCode::NO_MESSAGE_FOUND));
    }
    else if (rows > 0) {
        headerMap["code"] = QString::number(static_cast<int>(MessageCode::MESSAGES_FOUND));
    }
    QJsonArray array;
    while(query.next()) {
        QJsonObject messageObj;
        QString sender, receiver, title, content;
        QDateTime timestamp;
        receiver = query.value(0).toString();
        sender = query.value(1).toString();
        title = query.value(2).toString();
        content = query.value(3).toString();
        timestamp = QDateTime::fromString(query.value(4).toString(), Qt::ISODate);
        
        messageObj["timestamp"] = timestamp.toString(Qt::ISODate);
        messageObj["sender"] = sender;
        messageObj["receiver"] = receiver;
        messageObj["title"] = title;
        messageObj["content"] = content;
        array.append(messageObj);
        
    }
    
    QVariantMap map;
    map["header"] = headerMap;
    map["body"] = array.toVariantList();
    document = QJsonDocument::fromVariant(map);
    qInfo() << document;
    response = document.toJson();
    emit ready(response);
    
}

void ServerService::processGetSentMessagesRequest() {
    QJsonDocument document = QJsonDocument::fromJson(message);
    QJsonObject bodyObj = document["body"].toObject();
    QString login = bodyObj["login"].toString();
    
    db->Connect();
    QSqlQuery query = db->GenerateQuery();
    query.prepare("SELECT * FROM messages_by_login WHERE sender_login=:login");
    query.bindValue(":login", login);
    int rows = db->ProcessQuery(query);
    db->Disconnect();
    
    QByteArray response;
    QVariantMap headerMap;
    if (rows == 0) {
        headerMap["code"] = QString::number(static_cast<int>(MessageCode::NO_MESSAGE_FOUND));
    }
    else if (rows > 0) {
        headerMap["code"] = QString::number(static_cast<int>(MessageCode::MESSAGES_FOUND));
    }
    QJsonArray array;
    while(query.next()) {
        QJsonObject messageObj;
        QString sender, receiver, title, content;
        QDateTime timestamp;
        receiver = query.value(0).toString();
        sender = query.value(1).toString();
        title = query.value(2).toString();
        content = query.value(3).toString();
        timestamp = QDateTime::fromString(query.value(4).toString(), Qt::ISODate);
        
        messageObj["timestamp"] = timestamp.toString(Qt::ISODate);
        messageObj["sender"] = sender;
        messageObj["receiver"] = receiver;
        messageObj["title"] = title;
        messageObj["content"] = content;
        array.append(messageObj);
        
    }
    
    QVariantMap map;
    map["header"] = headerMap;
    map["body"] = array.toVariantList();
    document = QJsonDocument::fromVariant(map);
    qInfo() << document;
    response = document.toJson();
    emit ready(response);
}

