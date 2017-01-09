#ifndef TCPCLINET_H
#define TCPCLINET_H

#include <QTcpSocket>
#include <QObject>

class tcpclinet:public QObject
{
    Q_OBJECT
    QTcpSocket *Socket;
public:
    QTcpSocket *sock;
    tcpclinet(QTcpSocket * socket);

public slots:
    void datarecieve();
    void slotdisconnected();
    void slotconnected();

signals:
    void dataReady(QTcpSocket *sckt);
    void newConnection(QTcpSocket *sckt);
    void lostConnection(QTcpSocket *sckt);

};

#endif // TCPCLINET_H
