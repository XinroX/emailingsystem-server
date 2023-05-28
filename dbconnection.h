#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "IDbConnection.h"
#include <QtSql>

class DbConnection : public IDbConnection
{
    Q_OBJECT
public:
    explicit DbConnection(QObject *parent = nullptr);

    void Connect() override;
    void Disconnect() override;
    int ProcessQuery(QSqlQuery& query) override;
    QSqlQuery GenerateQuery() override;

signals:
private:
    QSqlDatabase db;

};



#endif // DBCONNECTION_H
