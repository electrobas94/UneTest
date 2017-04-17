#define NOMINMAX
#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QFile styles;
    styles.setFileName(a.applicationDirPath()+"/1.css");
    styles.open(QIODevice::ReadOnly);
    QByteArray dat;
    dat=styles.readAll();
    QString str=dat.data();
    a.setStyleSheet(str);
    MainWindow w;
    w.show();

    return a.exec();
}
