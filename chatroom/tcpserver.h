#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QThread>
#include <QTcpServer>
#include <QObject>
#include "tcpclinet.h"

class tcpserver:public QObject
{
    Q_OBJECT
public:
    explicit tcpserver(QObject *parent,int port);
    QList<tcpclinet *> tcpclientlist;
    QThread * ts1;
signals:
    void updateserver(QString,int);

public slots:
    void updateclient(QString,int);
    void slotdisconnected(int);
    void newConnection();

private:
    void incommingclient(int socketDescriptor);
    QTcpServer *ts;
};

#endif // TCPSERVER_H
