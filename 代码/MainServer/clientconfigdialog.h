#ifndef CLIENTCONFIGDIALOG_H
#define CLIENTCONFIGDIALOG_H
#include "tcpserver.h"
#include <QDialog>

namespace Ui {
class ClientConfigDialog;
}

class ClientConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientConfigDialog(QWidget *parent = 0,TcpServer * tcpServer = NULL);
    ~ClientConfigDialog();

private slots:

    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_pushButton_clicked();

private:
    Ui::ClientConfigDialog *ui;
    TcpServer * tcpServer;
    void init();
};

#endif // CLIENTCONFIGDIALOG_H
