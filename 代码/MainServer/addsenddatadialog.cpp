#include "addsenddatadialog.h"
#include "ui_addsenddatadialog.h"
#include "itemform.h"
#include "tool.h"
#include <QMessageBox>

AddSendDataDialog::AddSendDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSendDataDialog)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowFlags( windowFlags() | Qt::WindowMinimizeButtonHint |Qt::WindowMaximizeButtonHint);
    this->ui->cmdidEdit->setMaxLength(30);
    init();
}

void AddSendDataDialog::init()
{
    for(int i=0;i<4;i++)
    {
        QListWidgetItem *item = new QListWidgetItem;
        ui->listWidget->addItem(item);
        ItemForm *itemForm = new ItemForm;
        ui->listWidget->setItemWidget(item,itemForm);
        item->setSizeHint (QSize(itemForm->rect().width(),itemForm->rect().height()));
    }
}

AddSendDataDialog::~AddSendDataDialog()
{
    delete ui;
}


void AddSendDataDialog::on_addcmdBtn_clicked()
{
    QListWidgetItem *item = new QListWidgetItem;
    ui->listWidget->addItem(item);
    ItemForm *itemForm = new ItemForm;
    ui->listWidget->setItemWidget(item,itemForm);
    item->setSizeHint (QSize(itemForm->rect().width(),itemForm->rect().height()));
}

void AddSendDataDialog::on_delcmdBtn_clicked()
{
    int row = ui->listWidget->currentRow();
    if(row>=0)
    {
        ui->listWidget->takeItem(row);
    }
}

void AddSendDataDialog::on_commitBtn_clicked()
{
    if(ui->cmdidEdit->text()=="")
    {
        QMessageBox::about(NULL,"提示","命令编号不能为空");
        return ;
    }
    if(ui->listWidget->count()==0)
    {
        QMessageBox::about(NULL,"提示","命令数量不能为零");
        return ;
    }
    QMessageBox::StandardButton btn = QMessageBox::information(NULL,QStringLiteral("警告"),QStringLiteral("是否提交命令"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(btn == QMessageBox::Yes)
    {
        for(int i=0;i<ui->listWidget->count();i++)
        {
            ItemForm *itemForm = (ItemForm*)ui->listWidget->itemWidget(ui->listWidget->item(i));
            QString dataText = itemForm->getDataText();
            QDateTime dataTime = itemForm->getDataTime();
            emit addSenData(dataText,dataTime,ui->cmdidEdit->text());
            ui->listWidget->takeItem(i);
            i--;
        }
        QMessageBox::about(NULL,"提示","提交成功");
    }
}
