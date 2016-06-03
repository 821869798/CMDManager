#include "clockthread.h"
#include "tool.h"

ClockThread::ClockThread(QObject *parent,bool isStop):QThread(parent)
{
    this->isStop = isStop;
}

void ClockThread::stop()
{
    isStop = false;
}

void ClockThread::resume()
{
    isStop = true;
}

void ClockThread::run()
{
    while(true)
    {
        findDataToClock();
        this->sleep(5);
    }
}

void ClockThread::findDataToClock()
{
    QVector<RevData> *list = Tool::getInstance()->getClockData();
    QDateTime time = QDateTime::currentDateTime();
    for(int i=0;i<list->size();i++)
    {
        RevData temp = list->at(i);
        if(temp.time<time)
        {
            if(isStop&&temp.time.addSecs(600)>time)
            {
                emit updateMainToClock(temp.info);
            }
            list->remove(i);
            i--;
        }
    }
}
