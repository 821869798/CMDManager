#include "tool.h"

Tool *Tool::instance =  NULL;

Tool::Tool()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("subrecord.db");
    db.open();
    dataList = new QVector<RevData>;
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

QVector<RevData>* Tool::getClockData()
{
   return this->dataList;
}

void Tool::addNewRecord(QString id,QString info,QString time,QString orderTime)
{
    QSqlQuery query(this->db);
    query.prepare("insert into 记录(命令编号,信息,生效时间,下达时间) values(:id,:info,:time,:orderTime)");
    query.bindValue(":id",id);
    query.bindValue(":info",info);
    query.bindValue(":time",time);
    query.bindValue(":orderTime",orderTime);
    query.exec();
    RevData temp;
    temp.info = info;
    QDateTime t = QDateTime::fromString(time,"yyyy-MM-dd HH:mm:ss");
    temp.time.setDate(t.date());
    temp.time = temp.time.addSecs(3600*6);
    dataList->push_back(temp);
}
