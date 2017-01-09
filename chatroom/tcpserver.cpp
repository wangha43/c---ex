#include "tcpserver.h"

tcpserver::tcpserver(QObject *parent=0,int port=0)
{
    ts = new QTcpServer(this);
    ts->listen(QHostAddress::Any,port);
    connect(ts,SIGNAL(newConnection()),this,SLOT(newConnection()));
    moveToThread(ts1);
    ts1->start();
}

void tcpserver::newConnection()
{
    QTcpSocket *socket =ts->nextPendingConnection();
    socket->write("hello client\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);
    socket->close();
}

void tcpserver::updateclient(QString msg, int length){
    emit updateserver(msg,length);
    for(int i=0;i<tcpclientlist.count();i++){
        QTcpSocket *item = tcpclientlist.at(i)->sock;
        if(item->write(msg.toLatin1(),length)!=length)
            continue;
    }
}

void tcpserver::slotdisconnected(int descriptor){
    for(int i = 0; i<tcpclientlist.count();i++){
        QTcpSocket * item = tcpclientlist.at(i)->sock;
        if(item->socketDescriptor() == descriptor){
            tcpclientlist.removeAt(i);
            return;
        }
    }
    return;
}

void tcpserver::updateserver(QString msg,int length)
{
     qDebug("111");
}
