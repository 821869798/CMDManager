#ifndef ADDSENDDATADIALOG_H
#define ADDSENDDATADIALOG_H
#include "tcpsocket.h"
#include <QDialog>
#include <QDateTime>

namespace Ui {
class AddSendDataDialog;
}

class AddSendDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSendDataDialog(QWidget *parent = 0);
    ~AddSendDataDialog();

private slots:

    void on_addcmdBtn_clicked();

    void on_delcmdBtn_clicked();

    void on_commitBtn_clicked();
signals:
    void addSenData(QString dataText,QDateTime dataTime,QString id);
private:
    Ui::AddSendDataDialog *ui;
    void init();
};

#endif // ADDSENDDATADIALOG_H
