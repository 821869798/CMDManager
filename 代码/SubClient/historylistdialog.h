#ifndef HISTORYLISTDIALOG_H
#define HISTORYLISTDIALOG_H

#include <QDialog>

namespace Ui {
class HistoryListDialog;
}

class HistoryListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryListDialog(QWidget *parent = 0);
    ~HistoryListDialog();

private slots:
    void on_delRowBtn_clicked();

    void on_initBtn_clicked();

    void on_simpleQueryBtn_clicked();

    void on_clearBtn_clicked();

    void on_dataQueryBtn_clicked();

private:
    Ui::HistoryListDialog *ui;
    void init();
};

#endif // HISTORYLISTDIALOG_H
