#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QtNetwork>
#include <QDialog>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVector>
#include "clockthread.h"

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0,QString ipAddr = "",QString name = "");
    ~MainDialog();

private slots:
    void tcpConnected();
    void tcpDisconnected();
    void dataReceived();


    void on_receiveBtn_clicked();

    void on_historyBtn_clicked();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_checkBox_clicked(bool checked);
    void updateColckData(QString info);

private:
    Ui::MainDialog *ui;
    bool status;
    QTcpSocket *tcpSocket;
    QString ipAddr;
    QString name;
    QSystemTrayIcon *myTrayIcon;
    QVector<int> itemTypeList;
    ClockThread *ct;
    void init();
    void initSocket();
    void creatTrayIcon();
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);
    QMediaPlayer *player;
};

#endif // MAINDIALOG_H
