#include "tcpclinet.h"

tcpclinet::tcpclinet(QTcpSocket * socket):Socket(socket)
{
    this->sock = socket;
    connect(socket,SIGNAL(readyRead()),this,SLOT(datarecieve()));
    connect(socket,SIGNAL(connected()),this,SLOT(slotconnected()));
     connect(socket,SIGNAL(disconnected()),this,SLOT(slotdisconnected()));
}

void tcpclinet::datarecieve()
{
    emit dataReady(this->sock);
}

void tcpclinet::slotconnected(){
    emit newConnection(this->sock);
}

void tcpclinet::slotdisconnected()
{
    emit lostConnection(this->sock);
}

//void tcpclinet::datarecieve(){
//    while(bytesAvailable()>0){
//           int length = bytesAvailable();
//           char buff[1024];
//           read(buff,length);
//           QString msg = buff;
//           emit updateclient(msg,length);
//    }
//}

//void tcpclinet::slotdisconnected(){
//    emit disconnected(this->socketDescriptor());
//}
