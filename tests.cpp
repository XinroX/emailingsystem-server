#include "tests.h"
#include <QDebug>



TEST_F(ServerResponseTest, LoginFailedTest) {
    QByteArray data = prepareData(MessageCode::LOGIN_REQUEST);
    MockDbConnection db;
    ServerService service{nullptr, &db};
    EXPECT_CALL(db, Connect());
    EXPECT_CALL(db, Disconnect());
    EXPECT_CALL(db, ProcessQuery(testing::_)).Times(1).WillOnce(testing::Return(0));
    EXPECT_CALL(db, GenerateQuery()).Times(1).WillOnce(testing::Return(QSqlQuery()));

    setCode(MessageCode::LOGIN_REJECT);
    QObject::connect(&service, &ServerService::ready, this, &ServerResponseTest::read);
    service.StartHandling(data);


}

TEST_F(ServerResponseTest, LoginSucceedTest) {
    QByteArray data = prepareData(MessageCode::LOGIN_REQUEST);
    MockDbConnection db;
    ServerService service(nullptr, &db);
    EXPECT_CALL(db, Connect());
    EXPECT_CALL(db, Disconnect());
    EXPECT_CALL(db, ProcessQuery(testing::_)).Times(1).WillOnce(testing::Return(1));
    EXPECT_CALL(db, GenerateQuery()).Times(1).WillOnce(testing::Return(QSqlQuery()));

    setCode(MessageCode::LOGIN_ACCEPT);
    QObject::connect(&service, &ServerService::ready, this, &ServerResponseTest::read);

    service.StartHandling(data);

}

TEST_F(ServerResponseTest, LoginErrorTest) {
    QByteArray data = prepareData(MessageCode::LOGIN_REQUEST);
    MockDbConnection db;
    ServerService service(nullptr, &db);
    EXPECT_CALL(db, Connect());
    EXPECT_CALL(db, Disconnect());
    EXPECT_CALL(db, ProcessQuery(testing::_)).Times(1).WillOnce(testing::Return(2));
    EXPECT_CALL(db, GenerateQuery()).Times(1).WillOnce(testing::Return(QSqlQuery()));

    setCode(MessageCode::LOGIN_ERROR);
    QObject::connect(&service, &ServerService::ready, this, &ServerResponseTest::read);

    service.StartHandling(data);

}

TEST_F(ServerResponseTest, NoMessagesFoundTest) {
    QByteArray data = prepareData(MessageCode::GET_MESSAGES_RECEIVED);
    MockDbConnection db;
    ServerService service(nullptr, &db);
    EXPECT_CALL(db, Connect());
    EXPECT_CALL(db, Disconnect());
    EXPECT_CALL(db, ProcessQuery(testing::_)).Times(1).WillOnce(testing::Return(0));
    EXPECT_CALL(db, GenerateQuery()).Times(1).WillOnce(testing::Return(QSqlQuery()));

    setCode(MessageCode::NO_MESSAGE_FOUND);
    QObject::connect(&service, &ServerService::ready, this, &ServerResponseTest::read);

    service.StartHandling(data);

}

TEST_F(ServerResponseTest, MessageFoundTest) {
    QByteArray data = prepareData(MessageCode::GET_MESSAGES_RECEIVED);
    MockDbConnection db;
    ServerService service(nullptr, &db);
    EXPECT_CALL(db, Connect());
    EXPECT_CALL(db, Disconnect());
    EXPECT_CALL(db, ProcessQuery(testing::_)).Times(1).WillOnce(testing::Return(1));
    EXPECT_CALL(db, GenerateQuery()).Times(1).WillOnce(testing::Return(QSqlQuery()));

    setCode(MessageCode::MESSAGES_FOUND);
    QObject::connect(&service, &ServerService::ready, this, &ServerResponseTest::read);

    service.StartHandling(data);

}

TEST_F(ServerResponseTest, NoMessageSentFoundTest) {
    QByteArray data = prepareData(MessageCode::GET_MESSAGES_SENT);
    MockDbConnection db;
    ServerService service(nullptr, &db);
    EXPECT_CALL(db, Connect());
    EXPECT_CALL(db, Disconnect());
    EXPECT_CALL(db, ProcessQuery(testing::_)).Times(1).WillOnce(testing::Return(0));
    EXPECT_CALL(db, GenerateQuery()).Times(1).WillOnce(testing::Return(QSqlQuery()));

    setCode(MessageCode::NO_MESSAGE_FOUND);
    QObject::connect(&service, &ServerService::ready, this, &ServerResponseTest::read);

    service.StartHandling(data);

}

TEST_F(ServerResponseTest, MessagesSentFoundTest) {
    QByteArray data = prepareData(MessageCode::GET_MESSAGES_SENT);
    MockDbConnection db;
    ServerService service(nullptr, &db);
    EXPECT_CALL(db, Connect());
    EXPECT_CALL(db, Disconnect());
    EXPECT_CALL(db, ProcessQuery(testing::_)).Times(1).WillOnce(testing::Return(1));
    EXPECT_CALL(db, GenerateQuery()).Times(1).WillOnce(testing::Return(QSqlQuery()));

    setCode(MessageCode::MESSAGES_FOUND);
    QObject::connect(&service, &ServerService::ready, this, &ServerResponseTest::read);

    service.StartHandling(data);

}

