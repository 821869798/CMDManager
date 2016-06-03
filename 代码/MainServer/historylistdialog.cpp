#include "historylistdialog.h"
#include "ui_historylistdialog.h"
#include "tool.h"
#include <QMessageBox>

HistoryListDialog::HistoryListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryListDialog)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowFlags( windowFlags() | Qt::WindowMinimizeButtonHint |Qt::WindowMaximizeButtonHint);
    ui->tv1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tv1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->dateTimeEdit1->setDate(QDate::currentDate());
    ui->dateTimeEdit2->setDate(QDate::currentDate());
    init();
}

HistoryListDialog::~HistoryListDialog()
{
    delete ui;
}

void HistoryListDialog::init()
{
    Tool::getInstance();
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select 编号,命令编号,信息,生效时间,下达时间 from 记录 ORDER BY 下达时间 DESC;");
    ui->tv1->setModel(model);
    ui->tv1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tv1->hideColumn(0);
    ui->tv1->setColumnWidth(1,100);
    ui->tv1->setColumnWidth(2,900);
    ui->tv1->setColumnWidth(3,130);
    ui->tv1->setColumnWidth(4,130);
}

void HistoryListDialog::on_delRowBtn_clicked()
{
    QItemSelectionModel *selections = ui->tv1->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    if(selected.size()==0)
    {
        QMessageBox::about(NULL,"提示","没有选中行");
        return ;
    }
    QMessageBox::StandardButton btn = QMessageBox::information(NULL,QStringLiteral("警告"),QStringLiteral("确定删除选中行"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(btn != QMessageBox::Yes)
    {
        return;
    }
    QSqlQuery query(Tool::getInstance()->getDb());
    foreach (QModelIndex index, selected) {
        QModelIndex index1 = ui->tv1->model()->index(index.row(),0);
        QString id = ui->tv1->model()->data(index1).toString();
        query.exec("delete from 记录 where 编号='"+id+"';");
    }
    init();
}

void HistoryListDialog::on_initBtn_clicked()
{
    init();
}

void HistoryListDialog::on_simpleQueryBtn_clicked()
{
    QString id = ui->cmdidEdit->text();
    QString info = ui->infoEdit->text();
    QString sql = "select 编号,命令编号,信息,生效时间,下达时间 from 记录 where 1=1 and ";
    if(id!="")
    {
        sql += "命令编号='"+id+"' and ";
    }
    if(info!="")
    {
        sql += "信息 like '%"+info+"%' and ";
    }
    sql = sql.left(sql.size()-5);
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(sql);
    ui->tv1->setModel(model);
    ui->tv1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tv1->hideColumn(0);
    ui->tv1->setColumnWidth(1,100);
    ui->tv1->setColumnWidth(2,900);
    ui->tv1->setColumnWidth(3,130);
    ui->tv1->setColumnWidth(4,130);
}

void HistoryListDialog::on_clearBtn_clicked()
{
    ui->cmdidEdit->setText("");
    ui->infoEdit->setText("");
    init();
}

void HistoryListDialog::on_dataQueryBtn_clicked()
{
    QString date1 = ui->dateTimeEdit1->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString date2 = ui->dateTimeEdit2->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select 编号,命令编号,信息,生效时间,下达时间 from 记录 where 生效时间 between '"+date1+"' and '"+date2+"'");
    ui->tv1->setModel(model);
    ui->tv1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tv1->hideColumn(0);
    ui->tv1->setColumnWidth(1,100);
    ui->tv1->setColumnWidth(2,900);
    ui->tv1->setColumnWidth(3,130);
    ui->tv1->setColumnWidth(4,130);
}
