#ifndef MAINDIALOG_H
#define MAINDIALOG_H
#include "tcpserver.h"
#include "sendthread.h"
#include <QDialog>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QCloseEvent>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void thisQuit();

    void on_historyBtn_clicked();

    void on_readySendBtn_clicked();

    void on_openBtn_clicked();
    void updateServer(QString);


    void on_subclientBtn_clicked();
    void updateClient(QString message, int length,QString name,QString prompt);

    void on_addcmdBtn_clicked();
    void addSenData(QString dataText,QDateTime dataTime,QString id);

private:
    Ui::MainDialog *ui;
    void init();
    void creatTrayIcon();
    QSystemTrayIcon *myTrayIcon;
    void closeEvent(QCloseEvent *event);
    void getIpAddr();
    TcpServer *tcpServer;
    SendThread *sendThread;
    void changeEvent(QEvent *e);
    void insertMessage(QString message);

};

#endif // MAINDIALOG_H
