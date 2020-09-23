#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QtNetwork/QUdpSocket>
#include <QObject>

class MyClient : public QObject
{
    Q_OBJECT

private:
    QUdpSocket *sender_;

public:
    explicit MyClient(QObject *parent = 0);


signals:
public slots:

    void clientSend();
    void clientObtain();
};

#endif // MYCLIENT_H
