#include "mainwindow.h"
#include <QApplication>
#include <QGLFormat>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGLFormat format;
    format.setVersion(4,3);
    format.setProfile(QGLFormat::CoreProfile);


    MainWindow w;
    w.show();

    return a.exec();
}
