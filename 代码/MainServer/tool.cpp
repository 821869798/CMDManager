#include "tool.h"
#include <QJsonDocument>
#include <QJsonObject>

Tool *Tool::instance =  NULL;

Tool::Tool()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("record.db");
    db.open();
    sendList = new QVector<SendData>;
}

Tool *Tool::getInstance()
{
    if(instance==NULL)
    {
        instance = new Tool();
    }
    return instance;
}

QSqlDatabase Tool::getDb() const
{
    return db;
}

QString Tool::getJsonData(SendData sendData)
{
    QJsonObject object;
    object.insert("id",sendData.id);
    object.insert("info",sendData.dataText);
    object.insert("time",sendData.dateTime.toString("yyyy-MM-dd HH:mm:ss"));
    object.insert("orderTime",sendData.ordertime.toString("yyyy-MM-dd HH:mm:ss"));
    object.insert("type",1);
    QJsonDocument document;
    document.setObject(object);
    return QString(document.toJson());
}

void Tool::addSendData(QString dataText,QDateTime dateTime,QString id,QList<TcpSocket*> list)
{
    SendData sendData;
    sendData.dataText = dataText;
    sendData.dateTime = dateTime;
    sendData.id = id;
    sendData.ordertime = QDateTime::currentDateTime();
    //sendData.advance = advance;
    addNewRecord(sendData);
    for(int i=0;i<list.size();i++)
    {
        if(list.at(i)->name!="")
        {
            SendData temp;
            temp.name = list.at(i)->name;
            temp.id = id;
            temp.dataText = dataText;
            temp.dateTime = dateTime;
            temp.advance = list.at(i)->advance;
            temp.ordertime = sendData.ordertime;
            this->sendList->push_back(temp);
        }
    }
}

QVector<SendData> * Tool::getSendList()
{
    return this->sendList;
}

void Tool::addNewRecord(SendData sendData)
{
    QSqlQuery query(this->db);
    query.prepare("insert into 记录(命令编号,信息,生效时间,下达时间) values(:id,:info,:time,:nowtime)");
    query.bindValue(":id",sendData.id);
    query.bindValue(":info",sendData.dataText);
    query.bindValue(":time",sendData.dateTime.toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":nowtime",sendData.ordertime.toString("yyyy-MM-dd HH:mm:ss"));
    query.exec();
}
