#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QDebug>
#include <QJsonDocument>
class Receiver : public QObject {
    Q_OBJECT
public:
    explicit Receiver(QObject* parent = nullptr) : QObject{parent}{}

public slots:
    void print(const QByteArray& data) {
        QJsonDocument doc = QJsonDocument::fromJson(data);
        qInfo() << doc;
    }
};

#endif // RECEIVER_H
