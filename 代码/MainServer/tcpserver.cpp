#include "tcpserver.h"
#include <QDebug>

TcpServer::TcpServer(QObject *parent, int port) :
    QTcpServer(parent)
{
    this->listen(QHostAddress::Any, port);   //监听本机的IP地址和端口
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    TcpSocket *tcpSocket = new TcpSocket(this);
    connect(tcpSocket, SIGNAL(updateClients(QString)),
            this, SLOT(receiveClients(QString)));
    connect(tcpSocket, SIGNAL(disconnected(int)),
            this, SLOT(tcpDisconnected(int)));
    tcpSocket-> setSocketDescriptor (socketDescriptor);
    tcpSocketList.append(tcpSocket);             //在list 末尾插入数据
}

void TcpServer::updateClients(QString message, int length,QString name,QString prompt)
{
    //emit updateServer(message, length);   //发射信号
    for(int i = 0; i < tcpSocketList.count(); i++)
    {
        TcpSocket *temp = tcpSocketList.at(i);
        if(temp->name==name)
        {
            temp->write(message.toLocal8Bit());
            emit updateServer("已向"+temp->name+"发送信息:"+prompt+"...");
            break;
        }
//        if(temp->write(message.toLatin1(), length) != length)
//        {
//            continue;
//        }
    }
}

void TcpServer::receiveClients(QString message)
{
    emit updateServer(message);
}

void TcpServer::tcpDisconnected(int descriptor)
{
    for(int i = 0; i < tcpSocketList.count(); i++)
    {
        TcpSocket *temp = tcpSocketList.at(i);
        if(temp-> socketDescriptor () == descriptor)
        {
            if(temp->name!="")
            {
                emit updateServer(temp->name+"已经断开连接");
            }
            tcpSocketList.removeAt(i);
            return;
        }
    }
}

