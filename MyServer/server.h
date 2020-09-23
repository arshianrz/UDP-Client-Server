#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QUdpSocket>
#include <QObject>

class Server : public QObject
{
    Q_OBJECT

private:

    QUdpSocket *receiver_;
    int sum;
    int counter;
    int avg;

public:
explicit Server(QObject *parent = 0);

signals:
public slots:
    void serverReceive();
    void serverFeedback();



};
#endif // SERVER_H
