/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : editEntityWindow.cpp
 * @brief      : definition file for entity edit window
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include "entityEditWindow.h"
#include "ui_entityEditWindow.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                             CLASS DEFINITIONS                              //
//----------------------------------------------------------------------------//
/**
 * @brief default constructor
 */
EntityEditWindow::EntityEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntityEditWindow)
{
    ui->setupUi(this);
}

/**
 * @brief default destructor
 */
EntityEditWindow::~EntityEditWindow()
{
    delete ui;
}
/* on show callback */
void EntityEditWindow::showEvent(QShowEvent*event)
{
    clear();
    setupCombo(ui->editEntityTab->currentIndex());
}
/* on close callback */
void EntityEditWindow::closeEvent(QCloseEvent*event)
{
    entity = 0;
    MainWindow * p = qobject_cast<MainWindow*>(parent());
    p->updateCameraCombo();
}
/* clear all window data */
void EntityEditWindow::clear()
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
/* deletes entity */
void EntityEditWindow::deleteEntity()
{
    MainWindow * p = qobject_cast<MainWindow*>(parent());
    SimEngine * engine = p->getEngine();
    engine->removeEntity(entity);
    entity = 0;
}

void EntityEditWindow::openMenu(SimEntity *_entity)
{
    open();
    SimRobot* robot = dynamic_cast<SimRobot*>(_entity);
    SimSensor*sensor = dynamic_cast<SimSensor*>(_entity);
    SimEnvironment* env = dynamic_cast<SimEnvironment*>(_entity);
    QComboBox * combobox;
    int index;
    if(robot)
    {
        index =0;
        combobox = ui->robotComboBox;
    }
    else if(sensor)
    {
        index= 1;
        combobox = ui->sensorComboBox;
    }
    else if(env)
    {
        index =2;
        combobox = ui->environmentComboBox;
    }
    else
    {
        return;
    }
    ui->editEntityTab->setCurrentIndex(index);
    setupCombo(index);
    entity = _entity;
    combobox->setCurrentIndex(
                combobox->findData(QVariant::fromValue(_entity)));
    loadEntity(index);
}

/* sets up combo box */
void EntityEditWindow::setupCombo(int index)
{
    MainWindow * p = qobject_cast<MainWindow*>(parent());
    SimEngine * engine = p->getEngine();
    vector<SimEntity*>* ev = engine->getEntityVector();
    vector<SimEntity*>::iterator it;
    QComboBox * combo;

    bool shouldAdd = false;
    SimRobot * robot;
    SimSensor * sensor;
    SimEnvironment * env;
    // get combobox ptr
    switch(index)
    {
    case 0://robot
        combo = ui->robotComboBox;
        break;
    case 1://sensor
        combo = ui->sensorComboBox;
        break;
    case 2://environment
        combo = ui->environmentComboBox;
        break;
    default:
        break;
    }
    combo->clear();
    // loop through entity and add selectively
    for(it = ev->begin(); it != ev->end(); it++)
    {
        switch(index)
        {
        case 0:
            robot = dynamic_cast<SimRobot*>(*it);
            if(robot)
            {
                shouldAdd = true;
                robot = 0;
            }
            break;
        case 1:
            sensor = dynamic_cast<SimSensor*>(*it);
            if(sensor)
            {
                shouldAdd = true;
                sensor= 0;
            }
            break;
        case 2:
            env = dynamic_cast<SimEnvironment*>(*it);
            if(env)
            {
                shouldAdd = true;
                env = 0;
            }
            break;
        default:
            break;
        }
        if(shouldAdd)
        {
            combo->addItem(QString::fromStdString((*it)->getName()),
                           QVariant::fromValue<SimEntity*>(*it));
        }
        shouldAdd = false;
    }
    // if entity exists in current index,
    if(combo->count() > 0)
    {
        combo->currentIndexChanged(0);
    }
}
/* loads entity on GUI */
void EntityEditWindow::loadEntity(int index)
{
    clear();
    if(!entity)
    {
        return;
    }
    // fetch parameters selectively
    QLineEdit * name;
    QDoubleSpinBox * posX;
    QDoubleSpinBox * posY;
    QDoubleSpinBox * posZ;
    QDoubleSpinBox * rotX;
    QDoubleSpinBox * rotY;
    QDoubleSpinBox * rotZ;
    QTableWidget * advOptions;
    switch(index)
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
    name->setText(QString::fromStdString(entity->getName()));
    // upate pos/rot
    Point3D pos = entity->getPosition();
    posX->setValue(pos[0]);
    posY->setValue(pos[1]);
    posZ->setValue(pos[2]);

    array<double,3> rot = entity->getRotation();
    rotX->setValue(rot[0]);
    rotY->setValue(rot[1]);
    rotZ->setValue(rot[2]);

    // sets up advanced option
    int totalEntry = entity->getOptionLength();

    advOptions->setColumnCount(3);
    advOptions->setRowCount(totalEntry);
    QString label;
    QSpinBox * intbox;
    QDoubleSpinBox* dbbox;
    QLineEdit* lineedit;
    for(int i = 0; i<totalEntry; i++)
    {
        label = QString::fromStdString(entity->getOptionLabel(i));
        advOptions->setItem(i, 1, new QTableWidgetItem(label));
        switch(entity->getOptionType(i))
        {
        case INTEGER:
            advOptions->setItem(i, 0, new QTableWidgetItem("Int"));
            intbox = new QSpinBox(advOptions);
            intbox->setValue(entity->getOptionAsInt(i));
            advOptions->setCellWidget(i,2,intbox);
            break;
        case DOUBLE:
            advOptions->setItem(i, 0, new QTableWidgetItem("Double"));
            dbbox = new QDoubleSpinBox(advOptions);
            dbbox->setValue(entity->getOptionAsDouble(i));
            advOptions->setCellWidget(i,2,dbbox);
            break;
        case STRING:
            advOptions->setItem(i, 0, new QTableWidgetItem("String"));
            lineedit = new QLineEdit(advOptions);
            lineedit->setText(QString::fromStdString(entity->getOptionAsString(i)));
            advOptions->setCellWidget(i,2,lineedit);
            break;
        }
    }
    advOptions->horizontalHeader()->
            setSectionResizeMode( 0, QHeaderView::ResizeToContents);
    advOptions->horizontalHeader()->
            setSectionResizeMode( 1, QHeaderView::ResizeToContents);
    advOptions->horizontalHeader()->
            setSectionResizeMode( 2, QHeaderView::Stretch);
}
/* updates entity */
void EntityEditWindow::updateEntity()
{
    if(!entity)
    {
        return;
    }
    // fetch parameters selectively
    QLineEdit * name;
    QDoubleSpinBox * posX;
    QDoubleSpinBox * posY;
    QDoubleSpinBox * posZ;
    QDoubleSpinBox * rotX;
    QDoubleSpinBox * rotY;
    QDoubleSpinBox * rotZ;
    QTableWidget * advOptions;
    switch(ui->editEntityTab->currentIndex())
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

    // set name/pos/rot
    Point3D pos = {{posX->value(),posY->value(),posZ->value()}};
    array<double,3> rot = {{rotX->value(),rotY->value(),rotZ->value()}};
    entity->setName(name->text().toStdString());
    entity->setPosition(pos);
    entity->setRotation(rot);

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
}
//----------------------------------------------------------------------------//
//                           END CLASS DEFINITIONS                            //
//----------------------------------------------------------------------------//
void EntityEditWindow::on_robotComboBox_currentIndexChanged(int index)
{
    SimEntity* ent= qvariant_cast<SimEntity*>(
                ui->robotComboBox->itemData(index));
    entity = ent;
    loadEntity(0);
}

void EntityEditWindow::on_sensorComboBox_currentIndexChanged(int index)
{
    SimEntity* ent= qvariant_cast<SimEntity*>(
                ui->sensorComboBox->itemData(index));
    entity = ent;
    loadEntity(1);
}

void EntityEditWindow::on_environmentComboBox_currentIndexChanged(int index)
{
    SimEntity* ent= qvariant_cast<SimEntity*>(
                ui->environmentComboBox->itemData(index));
    entity = ent;
    loadEntity(2);
}

void EntityEditWindow::on_deleteButton_clicked()
{
    deleteEntity();
    setupCombo(ui->editEntityTab->currentIndex());
}

void EntityEditWindow::on_editEntityTab_currentChanged(int index)
{
    setupCombo(index);
}

void EntityEditWindow::on_buttonBox_accepted()
{
    updateEntity();
}
