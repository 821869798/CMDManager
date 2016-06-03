#ifndef SENDTHREAD_H
#define SENDTHREAD_H
#include "tcpserver.h"
#include <QThread>

class SendThread : public QThread
{
    Q_OBJECT
public:
    SendThread(QObject *parent = 0,TcpServer *tcpServer = 0);
    void stop();
private:
    TcpServer * tcpServer;
protected:
    void run();
    volatile bool toStop;
    void findToSend();
signals:
    void updateClient(QString, int, QString, QString);
};

#endif // SENDTHREAD_H
