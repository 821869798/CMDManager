#include "logindialog.h"
#include "ui_logindialog.h"
#include "maindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    init();

}

void LoginDialog::init()
{
    ui->nameEdit->setMaxLength(20);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_exitBtn_clicked()
{
    qApp->quit();
}

void LoginDialog::tcpConnected()
{
    tcpSocket->disconnectFromHost();
    QMessageBox::about(NULL,"提示","连接成功");
    MainDialog *md = new MainDialog(0,ipAddr,name);
    md->show();
    this->close();
}

void LoginDialog::on_connectionBtn_clicked()
{
    ipAddr = ui->ipEdit->text();
    name = ui->nameEdit->text();
    if(ipAddr==""||name=="")
    {
        QMessageBox::about(NULL,"提示","主机ip或名字不能为空");
        return;
    }
    int port = 8286;
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()),
    this, SLOT(tcpConnected()));
    tcpSocket-> connectToHost (ipAddr, port);
}
