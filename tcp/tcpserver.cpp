#include "tcpserver.h"

 tcpserver::tcpserver(QObject *parent ):QObject(parent){
     server = new QTcpServer(this);
        connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
    if(!server->listen(QHostAddress::Any,3000)){
        qDebug()<<"server could not start";
    }else{
        qDebug()<<"server started";
    }
}
void tcpserver::newConnection(){
    QTcpSocket *socket = server->nextPendingConnection();
    socket->write("hello,client , this is server speaking");
    socket->flush();
    qDebug()<<"server is talking to client";
    socket->waitForBytesWritten(3000);
    socket->close();
}
