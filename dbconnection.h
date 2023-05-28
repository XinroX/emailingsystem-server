#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "IDbConnection.h"

class DbConnection : public IDbConnection
{
    Q_OBJECT
public:
    explicit DbConnection(QObject *parent = nullptr);

    void Connect() override;
    void Disconnect() override;
    int ProcessQuery(QSharedPointer<QSqlQuery> query) override;

signals:
private:
    QSqlDatabase db;

};

#endif // DBCONNECTION_H
