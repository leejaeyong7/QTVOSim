/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : entityCreateWindow.cpp
 * @brief      : definition file for entity create window
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include "entityCreateWindow.h"
#include "ui_entityCreateWindow.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                              CLASS DEFINITION                              //
//----------------------------------------------------------------------------//
/**
 * @brief default constructor
 */
EntityCreateWindow::EntityCreateWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntityCreateWindow)
{
    ui->setupUi(this);
}
/**
 * @brief default destructor
 */
EntityCreateWindow::~EntityCreateWindow()
{
    delete ui;
}

/**
 * @brief show event callback, clears data and creates empty entity
 */
void EntityCreateWindow::showEvent(QShowEvent *event)
{
    entity =0;
    entityCreated = false;
    clear();
    on_createEntityTab_currentChanged(ui->createEntityTab->currentIndex());
}
/**
 * @brief close event callback, delete entity if necessary
 */
void EntityCreateWindow::closeEvent(QCloseEvent* event)
{
    if(!entityCreated)
    {
        deleteEntity();
    }
}


/**
 * @brief sets up advanced option table for entity
 */
void EntityCreateWindow::setupAdvancedOptionTable()
{
    // if there is no entity return
    if(!entity)
    {
        return;
    }
    // sets up current tab widget
    QTableWidget * currTableWidget;
    switch(ui->createEntityTab->currentIndex())
    {
    case 0: // ROBOT
        currTableWidget = ui->robotAdvancedOptions;
        break;
    case 1: // Sensor
        currTableWidget = ui->sensorAdvancedOptions;
        break;
    case 2:
        currTableWidget = ui->environmentAdvancedOptions;
        break;
    }
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

/**
 * @brief deletes entity
 */
void EntityCreateWindow::deleteEntity()
{
    cout<<"deleting entity"<<endl;
    if(!entity)
    {
        return;
    }
    delete entity;
    entity = 0;
}
/**
 * @brief clears data
 */
void EntityCreateWindow::clear()
{
    ui->robotName->clear();
    ui->sensorName->clear();
    ui->environmentName->clear();

    ui->robotPosX->clear();
    ui->robotPosY->clear();
    ui->robotPosZ->clear();
    ui->robotRotX->clear();
    ui->robotRotY->clear();
    ui->robotRotZ->clear();

    ui->sensorPosX->clear();
    ui->sensorPosY->clear();
    ui->sensorPosZ->clear();
    ui->sensorRotX->clear();
    ui->sensorRotY->clear();
    ui->sensorRotZ->clear();

    ui->environmentPosX->clear();
    ui->environmentPosY->clear();
    ui->environmentPosZ->clear();
    ui->environmentRotX->clear();
    ui->environmentRotY->clear();
    ui->environmentRotZ->clear();
    ui->robotAdvancedOptions->clear();
    ui->sensorAdvancedOptions->clear();
    ui->environmentAdvancedOptions->clear();
}

/**
 * @brief create entity based on parameters
 */
void EntityCreateWindow::on_buttonBox_accepted()
{
    MainWindow * p = qobject_cast<MainWindow*>(parent());
    SimEngine * engine = p->getEngine();

    // fetch parameters selectively
    QLineEdit * name;
    QDoubleSpinBox * posX;
    QDoubleSpinBox * posY;
    QDoubleSpinBox * posZ;
    QDoubleSpinBox * rotX;
    QDoubleSpinBox * rotY;
    QDoubleSpinBox * rotZ;
    QTableWidget * advOptions;
    switch(ui->createEntityTab->currentIndex())
    {
    case 0:
        name = ui->robotName;
        posX = ui->robotPosX;
        posY = ui->robotPosY;
        posZ = ui->robotPosZ;
        rotX = ui->robotRotX;
        rotY = ui->robotRotY;
        rotZ = ui->robotRotZ;
        advOptions = ui->robotAdvancedOptions;
        break;
    case 1:
        name = ui->sensorName;
        posX = ui->sensorPosX;
        posY = ui->sensorPosY;
        posZ = ui->sensorPosZ;
        rotX = ui->sensorRotX;
        rotY = ui->sensorRotY;
        rotZ = ui->sensorRotZ;
        advOptions = ui->sensorAdvancedOptions;
        break;
    case 2:
        name = ui->environmentName;
        posX = ui->environmentPosX;
        posY = ui->environmentPosY;
        posZ = ui->environmentPosZ;
        rotX = ui->environmentRotX;
        rotY = ui->environmentRotY;
        rotZ = ui->environmentRotZ;
        advOptions = ui->environmentAdvancedOptions;
        break;
    default:
        break;
    }
    Point3D pos = {{posX->value(),posY->value(),posZ->value()}};
    array<double,3> rot = {{rotX->value(),rotY->value(),rotZ->value()}};
    // sets up advanced option
    for(int i = 0; i < entity->getOptionLength(); i++)
    {
        QWidget * valueWidget = advOptions->cellWidget(i,2);
        QString valueType = advOptions->item(i,0)->text();
        if(valueType == "Int")
        {
            QSpinBox * spinbox = qobject_cast<QSpinBox*>(valueWidget);
            entity->setOption(i,spinbox->value());
        }
        else if(valueType == "Double")
        {

            QDoubleSpinBox * dspinbox=
                    qobject_cast<QDoubleSpinBox*>(valueWidget);

            entity->setOption(i,dspinbox->value());
        }
        else if(valueType =="String")
        {
            QLineEdit * lineEdit  = qobject_cast<QLineEdit*>(valueWidget);
            entity->setOption(i,lineEdit->text().toStdString());
        }
    }
    entity->setName(name->text().toStdString());
    entity->setPosition(pos);
    entity->setRotation(rot);
    // add entity
    engine->addEntity(entity);
    entityCreated = true;
    p->updateCameraCombo();
}
//----------------------------------------------------------------------------//
//                                GUI HANDLERS                                //
//----------------------------------------------------------------------------//
void EntityCreateWindow::on_createEntityTab_currentChanged(int index)
{
    deleteEntity();
    switch(index)
    {
    case 0: // Robot
        on_robotTypeComboBox_activated(0);
        break;
    case 1: // Sensor/QEv
        on_sensorTypeComboBox_activated(0);
        break;
    case 2: // environment
        on_environmentTypeComboBox_activated(0);
        break;
    default:
        break;
    }
    cout<<entity<<endl;

}

void EntityCreateWindow::on_robotTypeComboBox_activated(int index)
{
    deleteEntity();
    switch(index)
    {
    case 0:
        entity = new SimRobot("",0,0,0,0,0,0,0);
        break;
    default:
        break;
    }
    setupAdvancedOptionTable();
}

void EntityCreateWindow::on_sensorTypeComboBox_activated(int index)
{
    deleteEntity();
    switch(index)
    {
    case 0: // Camera
        entity = new SimCamera("",0,0,0,0,0,0,0,0,0);
        break;
    default:
        break;
    }
    setupAdvancedOptionTable();
}

void EntityCreateWindow::on_environmentTypeComboBox_activated(int index)
{
    deleteEntity();
    switch(index)
    {
    case 0: // Plane
        entity = new SimPlane("",0,0,0,0,0,0,0,0,0);
        break;
    default:
        break;

    }
    setupAdvancedOptionTable();
}
//----------------------------------------------------------------------------//
//                            END CLASS DEFINITION                            //
//----------------------------------------------------------------------------//
