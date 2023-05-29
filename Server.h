//
// Created by Mateusz Szybicki on 29/05/2023.
//

#ifndef EMAILINGSYSTEM_SERVER_SERVER_H
#define EMAILINGSYSTEM_SERVER_SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include <QThread>
#include <QThreadPool>
#include <QTcpSocket>
#include <QMap>
#include "serverservice.h"
#include "dbconnection.h"


class Server : public QTcpServer{
    Q_OBJECT
public:
    explicit Server(QObject* parent = nullptr);

public slots:
    void close();
    void disconnected();
    void readyRead();
    void readyResponse(const QByteArray& data);

protected:
    void incomingConnection(qintptr handle) override;
private:
    QList<QTcpSocket*> m_list;
    QMap<ServerService*, QTcpSocket*> m_map;
    IDbConnection* db;
};


#endif //EMAILINGSYSTEM_SERVER_SERVER_H
