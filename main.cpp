#include "mainwindow.h"
#include <QApplication>
#include "Engine/simEngine.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    SimEngine * engine = new SimEngine();
    return a.exec();
}
