#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout * glLayout = new QGridLayout();
    glwidget = new GLWidget(ui->openGLWidgetFrame);
    glLayout->addWidget(glwidget);
    ui->openGLWidgetFrame->setLayout(glLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}
