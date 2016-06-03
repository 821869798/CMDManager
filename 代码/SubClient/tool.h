#ifndef TOOL_H
#define TOOL_H
#include <QtSql>
#include <QVector>

struct RevData
{
    QString info;
    QDateTime time;
};

class Tool
{
public:
    Tool();
    static Tool * getInstance();
    QSqlDatabase getDb() const;
    void addNewRecord(QString id,QString info,QString time,QString orderTime);
    QVector<RevData>* getClockData();
private:
    static Tool *instance;
    QSqlDatabase db;
    QVector<RevData> *dataList;
};

#endif // TOOL_H
