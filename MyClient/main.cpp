#include <QCoreApplication>
#include "myclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyClient client;

    return a.exec();
}

