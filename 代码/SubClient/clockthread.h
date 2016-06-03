#ifndef CLOCKTHREAD_H
#define CLOCKTHREAD_H
#include <QThread>

class ClockThread : public QThread
{
    Q_OBJECT
private:
    void findDataToClock();
public:
    ClockThread(QObject *parent = 0,bool isStop = false);
    void stop();
    void resume();
protected:
    void run();
    bool isStop;
signals:
    void updateMainToClock(QString info);
};

#endif // CLOCKTHREAD_H
