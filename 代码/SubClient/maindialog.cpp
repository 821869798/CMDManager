#include "maindialog.h"
#include "ui_maindialog.h"
#include "historylistdialog.h"
#include "tool.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QMenu>

MainDialog::MainDialog(QWidget *parent,QString ipAddr,QString name) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    this->setWindowFlags( windowFlags() | Qt::WindowMinimizeButtonHint );
    this->ipAddr = ipAddr;
    this->name = name;
    ct = new ClockThread(this,true);
    connect(ct,&ClockThread::updateMainToClock,this,&MainDialog::updateColckData);
    ct->start();
    init();
    initSocket();
}

void MainDialog::init()
{
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setText("登陆名："+name);
    this->setFixedSize(this->size());
    QPalette palette;
    QPixmap pixmap(":/images/background.jpg");
    pixmap = pixmap.scaled(this->width(),this->height());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    player = new QMediaPlayer;
    QMediaPlaylist * playList = new QMediaPlaylist;
    playList->addMedia(QMediaContent(QUrl("qrc:/sounds/BGM.mp3")));
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playList);
    player->setVolume(60);

    creatTrayIcon();
}

void MainDialog::initSocket()
{
    int port = 8286;
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()),
    this, SLOT(tcpConnected()));
    connect(tcpSocket, SIGNAL(disconnected()),
    this, SLOT(tcpDisconnected()));
    connect(tcpSocket, SIGNAL(readyRead()),
    this, SLOT(dataReceived()));
    tcpSocket-> connectToHost (ipAddr, port);
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
    myTrayIcon->setToolTip(QStringLiteral("客户端"));   //托盘时，鼠标放上去的提示信息
    myTrayIcon->setContextMenu(myMenu);     //设置托盘上下文菜单
    myTrayIcon->show();
    this->connect(myTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void MainDialog::changeEvent(QEvent *e)
{
    if((e->type()==QEvent::WindowStateChange)&&this->isMinimized())
    {
        myTrayIcon->showMessage(QStringLiteral("提示"),QStringLiteral("客户端已最小化到托盘"));
        hide();
    }
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

void MainDialog::closeEvent(QCloseEvent *event)
{
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

MainDialog::~MainDialog()
{
    delete ui;
}


void MainDialog::tcpConnected()
{
    QJsonObject object;
    object.insert("name",name);
    object.insert("type",1);
    QJsonDocument document;
    document.setObject(object);
    QString message(document.toJson());
    tcpSocket->write(message.toLocal8Bit());
}

void MainDialog::tcpDisconnected()
{
    if(player->state()==QMediaPlayer::PlayingState)
    {
        player->stop();
    }
    QMessageBox::about(NULL,"提示","已断开连接");
    qApp->quit();
}

void MainDialog::dataReceived()
{
    if(tcpSocket-> bytesAvailable () > 0)
    {
        QByteArray datagram;
        datagram.resize(tcpSocket-> bytesAvailable ());
        tcpSocket->read(datagram.data(), datagram.length());
        //QString message = datagram.data();
        QString message = QString::fromLocal8Bit(datagram.data());
        //ui->label->setText(message);
        QJsonParseError json_error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(message.toUtf8(), &json_error);
        if(json_error.error == QJsonParseError::NoError)
        {
            if(jsonDocument.object()["type"].toInt()==1)
            {
                if(player->state()!=QMediaPlayer::PlayingState)
                {
                    player->play();
                }
                this->name = jsonDocument.object()["name"].toString();
                QString id = jsonDocument.object()["id"].toString();
                QString info = jsonDocument.object()["info"].toString();
                QString time = jsonDocument.object()["time"].toString();
                QString orderTime = jsonDocument.object()["orderTime"].toString();
                Tool::getInstance()->addNewRecord(id,info,time,orderTime);
                ui->listWidget->addItem(info);
                itemTypeList.push_back(0);
            }
        }
    }
}

void MainDialog::on_receiveBtn_clicked()
{
    int index = ui->listWidget->currentIndex().row();
    if(index==-1)
    {
        QMessageBox::about(NULL,"提示","没有选择内容");
    }
    else
    {
        QString info = ui->listWidget->item(index)->text();
        ui->listWidget->takeItem(index);
        if(itemTypeList.at(index)==0)
        {
            QJsonObject object;
            object.insert("info",info.left(10));
            object.insert("type",2);
            QJsonDocument document;
            document.setObject(object);
            QString msg(document.toJson());
            tcpSocket->write(msg.toLocal8Bit());
        }
        itemTypeList.remove(index);
        if(ui->listWidget->count()==0)
        {
            player->stop();
        }
    }
}

void MainDialog::on_historyBtn_clicked()
{
    HistoryListDialog *hl = new HistoryListDialog;
    hl->show();
}

void MainDialog::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        ct->resume();
    }
    else
    {
        ct->stop();
    }
}

void MainDialog::updateColckData(QString info)
{
    ui->listWidget->addItem(info);
    itemTypeList.push_back(1);
    if(player->state()!=QMediaPlayer::PlayingState)
    {
        player->play();
    }
}
