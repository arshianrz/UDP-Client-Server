#include "myclient.h"
#include <iostream>

MyClient::MyClient(QObject *parent) : QObject(parent)
{


    sender_ = new QUdpSocket(this);

    sender_->bind(QHostAddress("192.168.2.1"),1235);

    clientSend();

    connect(sender_,SIGNAL(readyRead()),this,SLOT(clientObtain()));

}

void MyClient::clientSend()
{

    QByteArray Data;

    qDebug()<<"Enter a number :";
    std::cin>>number_;

    //Sending integer into 4 Bytes.
    Data [0] = (number_ >> 24) & 0xFF;
    Data [1] = (number_ >> 16) & 0xFF;
    Data [2] = (number_ >> 8 ) & 0xFF;
    Data [3] = (number_ & 0xFF);

    sender_->writeDatagram(Data, QHostAddress("192.168.2.2"), 1234);

}

void MyClient::clientObtain()
{

    QHostAddress receiver;
    quint16 receivePort;

    QByteArray buffer;
    bool ok;

    buffer.resize(sender_->pendingDatagramSize());

    sender_->readDatagram(buffer.data(), buffer.size(), &receiver , &receivePort);

    avg=(buffer.toHex().toInt(&ok,16));

    qDebug()<<"Average  is :"<<avg;

    clientSend();
}
