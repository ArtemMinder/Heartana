#include "mainwindow.h"
#include "patient.h"
#include "logic.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w (nullptr);
    w.show();
    return a.exec();
}
