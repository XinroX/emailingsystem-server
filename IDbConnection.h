#ifndef IDBCONNECTION_H
#define IDBCONNECTION_H

#include <QObject>
#include <QSqlQuery>
#include <QSharedPointer>

class IDbConnection : public QObject {
    Q_OBJECT
public:
    virtual void Connect() = 0;
    virtual void Disconnect() = 0;
    virtual int ProcessQuery(QSqlQuery& query) = 0;
    virtual QSqlQuery GenerateQuery() = 0;
    virtual ~IDbConnection(){}
protected:
    explicit IDbConnection(QObject* parent = nullptr) : QObject{parent}{}
};


#endif // IDBCONNECTION_H
