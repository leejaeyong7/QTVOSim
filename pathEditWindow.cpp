#include "pathEditWindow.h"
#include "ui_pathEditWindow.h"

PathEditWindow::PathEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PathEditWindow)
{
    ui->setupUi(this);
}

PathEditWindow::~PathEditWindow()
{
    delete ui;
}
