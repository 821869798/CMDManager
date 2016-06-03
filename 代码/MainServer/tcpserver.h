#ifndef TCPSERVER_H
#define TCPSERVER_H
#include "tcpsocket.h"
#include <QtNetwork>

class TcpServer :public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0, int port = 0);
    QList<TcpSocket*> tcpSocketList;
    void updateClients(QString,int,QString,QString prompt);
protected:
    virtual void incomingConnection(qintptr socketDescriptor);
signals:
    void updateServer(QString);
public slots:
    void receiveClients(QString);
    void tcpDisconnected(int);
};

#endif // TCPSERVER_H
