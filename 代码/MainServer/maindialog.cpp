#include "maindialog.h"
#include "ui_maindialog.h"
#include "historylistdialog.h"
#include "readysenddialog.h"
#include "tool.h"
#include "clientconfigdialog.h"
#include "addsenddatadialog.h"
#include <QPalette>
#include <QtNetwork>
#include <QMessageBox>
#include <QStringListModel>
#include <QDebug>


MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    this->setWindowFlags( windowFlags() | Qt::WindowMinimizeButtonHint );
    init();
    sendThread = NULL;
    tcpServer = NULL;
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::init()
{
    //ui->groupBox->setStyleSheet("color:#ffffff;");
    ui->label->setStyleSheet("color:#ffffff;");
    this->setFixedSize(this->size());
    QPalette palette;
    QPixmap pixmap(":/images/background.jpg");
    pixmap = pixmap.scaled(this->width(),this->height());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
    creatTrayIcon();
    getIpAddr();
}

void MainDialog::getIpAddr()
{
    ui->ipEdit->setDisabled(true);
    QHostInfo info=QHostInfo::fromName(QHostInfo::localHostName());
    foreach(QHostAddress address,info.addresses())
    {
         if(address.protocol() == QAbstractSocket::IPv4Protocol)
         {
            ui->ipEdit->setText(address.toString());
            break;
         }
    }
}

void MainDialog::changeEvent(QEvent *e)
{
    if((e->type()==QEvent::WindowStateChange)&&this->isMinimized())
    {
        myTrayIcon->showMessage(QStringLiteral("提示"),QStringLiteral("主系统已最小化到托盘"));
        hide();
    }
}

void MainDialog::creatTrayIcon()
{
    QAction *quitAction = new QAction(QStringLiteral("退出"),this);
    this->connect(quitAction,&QAction::triggered,qApp,&QApplication::quit);
    QMenu *myMenu = new QMenu((QWidget*)QApplication::desktop());
    myMenu->addAction(quitAction);
    myTrayIcon = new QSystemTrayIcon(this);
    myTrayIcon->setIcon(QIcon(":/images/ico.ico"));   //设置图标图片
    setWindowIcon(QIcon(":/images/ico.ico"));  //把图片设置到窗口上
    myTrayIcon->setToolTip(QStringLiteral("主系统"));   //托盘时，鼠标放上去的提示信息
    myTrayIcon->setContextMenu(myMenu);     //设置托盘上下文菜单
    myTrayIcon->show();
    this->connect(myTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void MainDialog::on_addcmdBtn_clicked()
{
    if(tcpServer==NULL)
    {
        QMessageBox::about(NULL,"提示","服务还没开启");
        return;
    }
    AddSendDataDialog *addSend = new AddSendDataDialog;
    connect(addSend,&AddSendDataDialog::addSenData,this,&MainDialog::addSenData);
    addSend->show();
}

void MainDialog::addSenData(QString dataText, QDateTime dataTime, QString id)
{
    Tool::getInstance()->addSendData(dataText,dataTime,id,tcpServer->tcpSocketList);
}


void MainDialog::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:
        showNormal();
    default:
        break;
    }
}

void MainDialog::thisQuit()
{
    QMessageBox::StandardButton btn = QMessageBox::information(NULL,QStringLiteral("警告"),QStringLiteral("是否退出"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(btn == QMessageBox::Yes)
    {
        qDebug()<<"asd";
        //qApp->quit();
    }
    else
    {
        qDebug()<<"zxc";
    }
}

void MainDialog::closeEvent(QCloseEvent *event)
{
//    if (myTrayIcon->isVisible())
//    {
//        myTrayIcon->showMessage(QStringLiteral("提示"),QStringLiteral("主系统已最小化到托盘"));
//        hide();     //最小化
//        event->ignore();
//    }
//    else
//        event->accept();
    QMessageBox::StandardButton btn = QMessageBox::information(NULL,QStringLiteral("警告"),QStringLiteral("确定退出程序"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(btn == QMessageBox::Yes)
    {
        event->accept();
        qApp->quit();
    }
    else
    {
        event->ignore();
    }
}

void MainDialog::on_historyBtn_clicked()
{
    HistoryListDialog *historyList = new HistoryListDialog;
    historyList->show();
}

void MainDialog::on_readySendBtn_clicked()
{
    ReadySendDialog *readySendDialog = new ReadySendDialog;
    readySendDialog->show();
}

void MainDialog::on_openBtn_clicked()
{
    int port = 8286; //端口
    tcpServer = new TcpServer(this, port);
    connect(tcpServer, SIGNAL(updateServer(QString)),
             this, SLOT(updateServer(QString)));
    updateServer("开启服务");
    sendThread = new SendThread(this,tcpServer);
    sendThread->start();
    connect(sendThread,&SendThread::updateClient,this,&MainDialog::updateClient);
    ui->openBtn->setEnabled(false);
}

void MainDialog::updateServer(QString message)
{
    insertMessage(message);
}

void MainDialog::insertMessage(QString message)
{
    ui->listWidget->insertItem(0,message);
    if(ui->listWidget->count()>30)
    {
        ui->listWidget->takeItem(ui->listWidget->count()-1);
    }
}

void MainDialog::on_subclientBtn_clicked()
{
    ClientConfigDialog *cd = new ClientConfigDialog(0,tcpServer);
    cd->show();
}

void MainDialog::updateClient(QString message, int length, QString name, QString prompt)
{
    tcpServer->updateClients(message,length,name,prompt);
}
