#include "dbconnection.h"
#include <memory>
#include <QDebug>
#include <QSqlError>

DbConnection::DbConnection(QObject *parent)
    : IDbConnection{parent}
{
    db = QSqlDatabase::addDatabase("QPSQL", "test");
    db.setHostName("192.168.1.33");
    db.setPort(5432);
    db.setDatabaseName("projekt");
    db.setUserName("projekt");
    db.setPassword("123");

    qInfo() << db.connectionNames();
    qInfo() << QSqlDatabase::drivers();
}

void DbConnection::Connect() {
    qInfo() << db.isValid();
    bool ok = db.open();
    qInfo() << ok;
    qInfo() << db.lastError().text();
}


void DbConnection::Disconnect() {
    db.close();
}

int DbConnection::ProcessQuery(QSqlQuery& query) {
    qInfo() << db.isOpen();
    query.exec();
    qInfo() << db.lastError().text();
    qInfo() << query.lastError().text();
    return query.numRowsAffected();
}

QSqlQuery DbConnection::GenerateQuery() {
    return QSqlQuery(db);
}