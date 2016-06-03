#include "itemform.h"
#include "ui_itemform.h"

ItemForm::ItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemForm)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setDate(QDate::currentDate());
}

QString ItemForm::getDataText()
{
    return this->ui->msgEdit->toPlainText();
}

QDateTime ItemForm::getDataTime()
{
    return this->ui->dateTimeEdit->dateTime();
}

ItemForm::~ItemForm()
{
    delete ui;
}
