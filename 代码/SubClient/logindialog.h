#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QtNetwork>
#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_exitBtn_clicked();
    void tcpConnected();
    void on_connectionBtn_clicked();


private:
    Ui::LoginDialog *ui;
    QTcpSocket *tcpSocket;
    void init();
    QString ipAddr;
    QString name;
};

#endif // LOGINDIALOG_H
