#ifndef ITEMFORM_H
#define ITEMFORM_H

#include <QWidget>

namespace Ui {
class ItemForm;
}

class ItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit ItemForm(QWidget *parent = 0);
    ~ItemForm();

    QString getDataText();
    QDateTime getDataTime();
private:
    Ui::ItemForm *ui;
};

#endif // ITEMFORM_H
