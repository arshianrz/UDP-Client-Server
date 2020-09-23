#include "server.h"
#include <QtNetwork/QUdpSocket>
#include <iostream>


Server::Server(QObject *parent):QObject(parent)
{
    receiver_ = new QUdpSocket(this);

    receiver_->bind(QHostAddress("192.168.2.2"),1234);

    connect(receiver_,SIGNAL(readyRead()),this,SLOT(serverReceive()));
    sum=0;
    counter=1;
}

void Server::serverReceive()
{
    qDebug()<<"Data receiving by server ...";

    QByteArray buffer;

    buffer.resize(receiver_->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    bool ok;
    receiver_->readDatagram(buffer.data(), buffer.size(), &sender , &senderPort);


    sum+=buffer.toHex().toInt(&ok,16);

    qDebug()<<"Data is :"<<buffer.toHex().toInt(&ok,16);
    qDebug()<<"Sum  is :"<<sum;

    serverFeedback();

}

void Server::serverFeedback()
{

    avg=sum/counter;

    QByteArray avgHolder;

    avgHolder[0] = (avg >>  24) & 0xFF;
    avgHolder[1] = (avg >>  16) & 0xFF;
    avgHolder[2] = (avg >>  8 ) & 0xFF;
    avgHolder[3] = (avg & 0xFF);

    receiver_->writeDatagram(avgHolder,QHostAddress("192.168.2.1"), 1235);
    ++counter;


    qDebug()<<"Average server is :"<<avg;
}


