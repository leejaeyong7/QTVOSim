#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qirrlichtwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QIrrlichtWidget * getIrrlichtWidget()
    {
        return irrlichtWidget;
    };
private slots:
    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QIrrlichtWidget *irrlichtWidget;
};

#endif // MAINWINDOW_H
