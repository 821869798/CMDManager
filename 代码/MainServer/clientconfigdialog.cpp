#include "clientconfigdialog.h"
#include "ui_clientconfigdialog.h"
#include <QMessageBox>

ClientConfigDialog::ClientConfigDialog(QWidget *parent,TcpServer * tcpServer) :
    QDialog(parent),
    ui(new Ui::ClientConfigDialog)
{
    ui->setupUi(this);
    ui->nameLabel->setAlignment(Qt::AlignCenter);
    this->tcpServer = tcpServer;
    ui->advanceEdit->setValidator(new QIntValidator(0,100,this));
    init();
}

void ClientConfigDialog::init()
{
    if(tcpServer!=NULL)
    {
        QList<TcpSocket*> list = tcpServer->tcpSocketList;
        for(int i=0;i<list.size();i++)
        {
            ui->listWidget->addItem(list.at(i)->name);
        }
    }
}

ClientConfigDialog::~ClientConfigDialog()
{
    delete ui;
}


void ClientConfigDialog::on_listWidget_currentTextChanged(const QString &currentText)
{
    QList<TcpSocket*> list = tcpServer->tcpSocketList;
    for(int i = 0;i<list.size();i++)
    {
        if(list.at(i)->name==currentText)
        {
            ui->nameLabel->setText(currentText);
            ui->advanceEdit->setText(QString::number(list.at(i)->advance));
        }
    }
}

void ClientConfigDialog::on_pushButton_clicked()
{
    QList<TcpSocket*> list = tcpServer->tcpSocketList;
    for(int i = 0;i<list.size();i++)
    {
        if(list.at(i)->name==ui->nameLabel->text())
        {
            int advance = ui->advanceEdit->text().toInt();
            list.at(i)->advance = advance;
            QMessageBox::about(NULL,"提示","修改提前天数成功");
        }
    }
}
