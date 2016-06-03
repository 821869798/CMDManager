#include "readysenddialog.h"
#include "ui_readysenddialog.h"
#include "tool.h"
#include <QStandardItemModel>
#include <QMessageBox>

ReadySendDialog::ReadySendDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadySendDialog)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowFlags( windowFlags() | Qt::WindowMinimizeButtonHint |Qt::WindowMaximizeButtonHint);
    ui->tv1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tv1->setSelectionBehavior(QAbstractItemView::SelectRows);
    initTableView();
}

ReadySendDialog::~ReadySendDialog()
{
    delete ui;
}

void ReadySendDialog::initTableView()
{
    QVector<SendData> * list = Tool::getInstance()->getSendList();
    QStandardItemModel * model = new QStandardItemModel;
    for(int i=0;i<list->size();i++)
    {
        SendData sendData = list->at(i);
        model->setItem(i,0,new QStandardItem(sendData.id));
        model->setItem(i,1,new QStandardItem(sendData.name));
        model->setItem(i,2,new QStandardItem(sendData.dateTime.toString("yyyy-MM-dd HH:mm:ss")));
        model->setItem(i,3,new QStandardItem(QString::number(sendData.advance)));
        model->setItem(i,4,new QStandardItem(sendData.ordertime.toString("yyyy-MM-dd HH:mm:ss")));
        model->setItem(i,5,new QStandardItem(sendData.dataText));
    }
    model->setHorizontalHeaderItem(0,new QStandardItem(QStringLiteral("命令编号")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QStringLiteral("接收方")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QStringLiteral("生效时间")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QStringLiteral("提前天数")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QStringLiteral("下达时间")));
    model->setHorizontalHeaderItem(5,new QStandardItem(QStringLiteral("发送信息")));
    ui->tv1->setModel(model);
    ui->tv1->setColumnWidth(0,100);
    ui->tv1->setColumnWidth(1,150);
    ui->tv1->setColumnWidth(2,140);
    ui->tv1->setColumnWidth(3,80);
    ui->tv1->setColumnWidth(4,140);
    ui->tv1->setColumnWidth(5,700);
}

void ReadySendDialog::on_delRowBtn_clicked()
{
    QItemSelectionModel *selections = ui->tv1->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    if(selected.size()==0)
    {
        QMessageBox::about(NULL,"提示","没有选中行");
        return ;
    }
    QMessageBox::StandardButton btn = QMessageBox::information(NULL,QStringLiteral("警告"),QStringLiteral("确定删除该命令？"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(btn != QMessageBox::Yes)
    {
        return;
    }
    QVector<SendData> * list = Tool::getInstance()->getSendList();
    QVector<int> vec;
    foreach (QModelIndex index, selected) {
        if(!vec.contains(index.row()))
        {
            vec.push_back(index.row());
        }
    }
    qSort(vec.begin(),vec.end());
    int flag = 0;
    foreach (int i,vec) {
        list->remove(i-flag);
        flag++;
    }
    initTableView();
}
