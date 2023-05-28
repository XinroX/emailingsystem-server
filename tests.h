#ifndef TESTS_H
#define TESTS_H

#include <QObject>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "IDbConnection.h"
#include "serverservice.h"

class MockDbConnection : public IDbConnection {
public:
    MockDbConnection() : IDbConnection{nullptr}{}

    MOCK_METHOD(void, Connect, ());
    MOCK_METHOD(void, Disconnect, ());
    MOCK_METHOD(int, ProcessQuery, (QSqlQuery&));
    MOCK_METHOD(QSqlQuery, GenerateQuery, ());
};

class ServerResponseTest : public QObject, public testing::Test/*WithParam<std::tuple<int, MessageCode>> */{
    Q_OBJECT
protected:
    void SetUp() override {}
    void TearDown() override {}
    QByteArray prepareData(MessageCode code) {
        QVariantMap headerMap;
        headerMap["code"] = QString::number(static_cast<int>(code));
        QVariantMap map;
        map["header"] = headerMap;
        QJsonDocument document = QJsonDocument::fromVariant(map);
        return document.toJson();
    }
    void setCode(MessageCode code){
        this->mCode = code;
    }

public slots:
    void read(const QByteArray& data) {
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject obj = document["header"].toObject();
        int code = obj["code"].toString().toInt();
        qInfo() << obj << '\n' << code;
        ASSERT_EQ(static_cast<int>(mCode), code);
    }
protected:
    MessageCode mCode;
};

#endif // TESTS_H
