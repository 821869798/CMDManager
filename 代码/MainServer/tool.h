#ifndef TOOL_H
#define TOOL_H
#include "tcpsocket.h"
#include <QtSql>
#include <QVector>

struct SendData
{
    QString id;
    QString name;
    QString dataText;
    QDateTime dateTime;
    QDateTime ordertime;
    int advance;
};

class Tool
{
public:
    Tool();
    static Tool * getInstance();
    QSqlDatabase getDb() const;

    QString getJsonData(SendData sendData);
    void addSendData(QString dataText,QDateTime dateTime,QString id,QList<TcpSocket*> list);
    QVector<SendData> *getSendList();
    void addNewRecord(SendData sendData);
private:
    QVector<SendData> *sendList;
    static Tool *instance;
    QSqlDatabase db;
};

#endif // TOOOL_H
