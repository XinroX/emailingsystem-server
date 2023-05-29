//
// Created by Mateusz Szybicki on 29/05/2023.
//

#include "Server.h"

Server::Server(QObject* parent) : QTcpServer{parent} {
    db = new DbConnection;
}

void Server::close() {
    foreach(QTcpSocket* socket, m_list) {
        socket->close();
    }
    qDeleteAll(m_list);
    m_list.clear();
}

void Server::incomingConnection(qintptr handle) {
    QTcpSocket* socket = new QTcpSocket;
    socket->setSocketDescriptor(handle);
    if (!socket->waitForConnected(3000)) {
        delete socket;
        return;
    }
    m_list.append(socket);
    connect(socket, &QTcpSocket::disconnected, this, &Server::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Server::readyRead);
}

void Server::readyRead() {
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    ServerService* service = new ServerService{nullptr, db};
    m_map[service] = socket;
    connect(service, &ServerService::ready, this, &Server::readyResponse);
    service->StartHandling(socket->readAll());
}

void Server::readyResponse(const QByteArray &data) {
    ServerService* service = qobject_cast<ServerService*>(sender());
    QTcpSocket* socket = m_map[service];
    socket->write(data);
    socket->waitForBytesWritten(5000);
    socket->close();
    m_map.remove(service);
    m_list.removeAll(socket);
    delete service;
    delete socket;
}

void Server::disconnected() {
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    socket->close();
    m_list.removeAll(socket);
    foreach(ServerService* service, m_map.keys()) {
        if (m_map[service] == socket) {
            m_map.remove(service);
            delete service;
            break;
        }
    }
    delete socket;
}