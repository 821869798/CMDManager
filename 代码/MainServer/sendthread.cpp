#include "sendthread.h"
#include "tool.h"
#include <QDebug>

SendThread::SendThread(QObject *parent,TcpServer * tcpServer):QThread(parent)
{
    toStop = false;
    this->tcpServer = tcpServer;
}

void SendThread::stop()
{
    toStop = true;
}

void SendThread::run()
{
    while(!toStop)
    {
        this->sleep(1);
        findToSend();
    }
}

void SendThread::findToSend()
{
    QVector<SendData> *list = Tool::getInstance()->getSendList();
    QDateTime time = QDateTime::currentDateTime();
    for(int i=0;i<list->size();i++)
    {
        SendData sendData = list->at(i);
        if(sendData.dateTime.addDays(-sendData.advance)<time)
        {
            QString data = Tool::getInstance()->getJsonData(sendData);
            emit updateClient(data,data.length(),sendData.name,sendData.dataText.left(10));
            list->remove(i);
            i--;
            break;
        }
    }
}


