#include "tcpsocket.h"
#include <QJsonDocument>
#include <QJsonObject>

TcpSocket::TcpSocket(QObject *parent) :    QTcpSocket(parent)
{
    advance = 0;
    connect(this, SIGNAL(readyRead()),
            this, SLOT(dataReceived()));    //准备接收
    connect(this, SIGNAL(disconnected()),
            this, SLOT(datadisconnected())); //断开连接信号
}

void TcpSocket::dataReceived()
{
    while(this-> bytesAvailable () > 0) //检查字节数
    {
        char buf[1024];
        int length = bytesAvailable ();
        QByteArray dataread = this->readAll();
        QString message = QString::fromLocal8Bit(dataread);
        QJsonParseError json_error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(message.toUtf8(), &json_error);
        if(json_error.error == QJsonParseError::NoError)
        {
            if(jsonDocument.object()["type"].toInt()==1)
            {
                this->name = jsonDocument.object()["name"].toString();
                emit updateClients(name+"已成功连接");  //发射信号
            }
            if(jsonDocument.object()["type"].toInt()==2)
            {
                QString info = jsonDocument.object()["info"].toString();
                emit updateClients(this->name+"已接收消息:"+info+"...");  //发射信号
            }
        }
    }
}

void TcpSocket::datadisconnected()
{
    emit disconnected(this-> socketDescriptor ());
}
