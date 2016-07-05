/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : mainwindow.cpp
 * @brief      : main window definition file
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include "mainwindow.h"
#include "ui_mainwindow.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                              CLASS DEFINITION                              //
//----------------------------------------------------------------------------//
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* setup opengl widget */
    QGridLayout * glLayout = new QGridLayout();
    glwidget = new GLWidget(ui->openGLWidgetFrame);
    glLayout->addWidget(glwidget);
    ui->openGLWidgetFrame->setLayout(glLayout);
    /* setup dialogs */
    entityCreateWindow = new EntityCreateWindow(this);
    entityEditWindow = new EntityEditWindow(this);
    pathEditWindow = new PathEditWindow(this);
    updateCameraCombo();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::updateCameraCombo()
{
    cout<<"updating"<<endl;
    if(!glwidget->getEngine())
    {
        return;
    }
    if(!glwidget->getEngine()->getCamera())
    {
        return;
    }
    // update main camera combobox
    QComboBox* mainCombo = ui->mainCameraComboBox;
    mainCombo->clear();
    vector<SimEntity*>* ev = glwidget->getEngine()->getEntityVector();
    vector<SimEntity*>::iterator it;
    int index = 0;
    int camIndex = 0;
    for(it =ev->begin(); it != ev->end(); it++)
    {
        if(dynamic_cast<SimCamera*>(*it))
        {
            mainCombo->addItem(QString::fromStdString((*it)->getName()),
                               QVariant::fromValue<SimEntity*>(*it));
            if((*it) == glwidget->getEngine()->getCamera())
            {
                camIndex = index;
            }
            index++;
        }
    }
    mainCombo->setCurrentIndex(camIndex);
}
//----------------------------------------------------------------------------//
//                            END CLASS DEFINITION                            //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                               GUI FUNCTIONS                                //
//----------------------------------------------------------------------------//
void MainWindow::on_actionExit_triggered()
{
    close();
}
void MainWindow::on_cameraPosX_valueChanged(double arg1)
{
    Point3D p  = glwidget->getEngine()->getCamera()->getPosition();
    p[0] = arg1;
    glwidget->getEngine()->getCamera()->setPosition(p);
}

void MainWindow::on_cameraPosY_valueChanged(double arg1)
{
    Point3D p  = glwidget->getEngine()->getCamera()->getPosition();
    p[1] = arg1;
    glwidget->getEngine()->getCamera()->setPosition(p);
}

void MainWindow::on_cameraPosZ_valueChanged(double arg1)
{
    Point3D p  = glwidget->getEngine()->getCamera()->getPosition();
    p[2] = arg1;
    glwidget->getEngine()->getCamera()->setPosition(p);
}

void MainWindow::on_cameraRotX_valueChanged(double arg1)
{
    array<double,3> r  = glwidget->getEngine()->getCamera()->getRotation();
    r[0] = arg1;
    glwidget->getEngine()->getCamera()->setRotation(r);

}

void MainWindow::on_cameraRotY_valueChanged(double arg1)
{
    array<double,3> r  = glwidget->getEngine()->getCamera()->getRotation();
    r[1] = arg1;
    glwidget->getEngine()->getCamera()->setRotation(r);

}

void MainWindow::on_cameraRotZ_valueChanged(double arg1)
{
    array<double,3> r  = glwidget->getEngine()->getCamera()->getRotation();
    r[2] = arg1;
    glwidget->getEngine()->getCamera()->setRotation(r);
}

void MainWindow::on_actionEntityAdd_triggered()
{
    entityCreateWindow->exec();
}

void MainWindow::on_actionEntityEdit_triggered()
{
    entityEditWindow->exec();
}

void MainWindow::on_actionImport_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "~/",
                "PLY file (.ply)");


}

void MainWindow::on_mainCameraSettingsButton_clicked()
{
    entityEditWindow->openMenu(glwidget->getEngine()->getCamera());
}

void MainWindow::on_mainCameraComboBox_currentIndexChanged(int index)
{
    SimEntity* ent= qvariant_cast<SimEntity*>(
                ui->mainCameraComboBox->itemData(index));
    glwidget->getEngine()->setCamera((SimCamera*)ent);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index)
    {
    case 0:// camera mode
        glwidget->setEditMode(false);
        break;
    case 1:
        glwidget->setEditMode(true);
        break;
    default:
        break;
    }
}

void MainWindow::on_entityPlaceComboBox_currentIndexChanged(int index)
{
    setupEditEntity(index);
}

void MainWindow::setupEditEntity(int index)
{
    if(glwidget->getEditEntity())
    {
        glwidget->deleteEditEntity();
    }
    SimEnvironment * entity;
    switch(index)
    {
    case 0: // simplane
        entity = new SimPlane("",0,0,0,0,0,0,0,0);
        glwidget->setEditEntity(entity);
        break;
    default:
        break;
    }
    ui->entityName->setText("");
    ui->entityPosX->setValue(0);
    ui->entityPosY->setValue(0);
    ui->entityPosZ->setValue(0);
    ui->entityRotX->setValue(0);
    ui->entityRotY->setValue(0);
    ui->entityRotZ->setValue(0);
    QTableWidget * currTableWidget= ui->entityAdvancedOption;
    currTableWidget->clear();
    int totalEntry = entity->getOptionLength();
    currTableWidget->setColumnCount(3);
    currTableWidget->setRowCount(totalEntry);
    QString label;
    for(int i = 0; i<totalEntry; i++)
    {
        label = QString::fromStdString(entity->getOptionLabel(i));
        currTableWidget->setItem(i, 1, new QTableWidgetItem(label));
        switch(entity->getOptionType(i))
        {
        case INTEGER:
            currTableWidget->setItem(i, 0, new QTableWidgetItem("Int"));
            currTableWidget->setCellWidget(i,2,new QSpinBox(currTableWidget));
            break;
        case DOUBLE:
            currTableWidget->setItem(i, 0, new QTableWidgetItem("Double"));
            currTableWidget->setCellWidget(i,2,new QDoubleSpinBox(currTableWidget));
            break;
        case STRING:
            currTableWidget->setItem(i, 0, new QTableWidgetItem("String"));
            currTableWidget->setCellWidget(i,2,new QLineEdit(currTableWidget));
            break;
        }
    }
    currTableWidget->horizontalHeader()->
            setSectionResizeMode( 0, QHeaderView::ResizeToContents);
    currTableWidget->horizontalHeader()->
            setSectionResizeMode( 1, QHeaderView::ResizeToContents);
    currTableWidget->horizontalHeader()->
            setSectionResizeMode( 2, QHeaderView::Stretch);
}

void MainWindow::on_createEntityButton_clicked()
{
    setupEditEntity(ui->entityPlaceComboBox->currentIndex());
}

void MainWindow::on_setEntityButton_clicked()
{
    glwidget->placeEditEntity();
}

void MainWindow::on_actionEditPath_triggered()
{
    pathEditWindow->exec();
}
