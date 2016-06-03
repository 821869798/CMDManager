#include "maindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDialog mainDialog;
    mainDialog.show();
    return a.exec();
}
