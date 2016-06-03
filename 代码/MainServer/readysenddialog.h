#ifndef READYSENDDIALOG_H
#define READYSENDDIALOG_H

#include <QDialog>

namespace Ui {
class ReadySendDialog;
}

class ReadySendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReadySendDialog(QWidget *parent = 0);
    ~ReadySendDialog();

private slots:
    void on_delRowBtn_clicked();

private:
    Ui::ReadySendDialog *ui;
    void initTableView();
};

#endif // READYSENDDIALOG_H
