/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : entityCreateWindow.h
 * @brief      : definition file for entity create window
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
#ifndef ENTITYCREATEWINDOW_H
#define ENTITYCREATEWINDOW_H
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include <QDialog>
#include "mainwindow.h"
#include "Engine/simEntityList.h"
#include "Engine/simEngine.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
class MainWindow;
namespace Ui {
class EntityCreateWindow;
}
//----------------------------------------------------------------------------//
//                             CLASS DECLARATION                              //
//----------------------------------------------------------------------------//
class EntityCreateWindow : public QDialog
{
    Q_OBJECT

public:
    /* default constructor */
    explicit EntityCreateWindow(QWidget *parent = 0);
    ~EntityCreateWindow();

    /* GUI functions */
private slots:

    void on_createEntityTab_currentChanged(int index);

    void on_robotTypeComboBox_activated(int index);

    void on_sensorTypeComboBox_activated(int index);

    void on_environmentTypeComboBox_activated(int index);

    void on_buttonBox_accepted();
    
private:
    /* on show callback */
    void showEvent(QShowEvent*event);
    /* on close callback */
    void closeEvent(QCloseEvent*event);
    /* clear all window data */
    void clear();
    /* deletes entity */
    void deleteEntity();

    /* setup helper functions */
    void setupAdvancedOptionTable();
    Ui::EntityCreateWindow *ui;
    /* checkes whether entity is created */
    bool entityCreated;

    /* holds currently simentity */
    SimEntity* entity;
};
//----------------------------------------------------------------------------//
//                           END CLASS DECLARATION                            //
//----------------------------------------------------------------------------//
#endif // ENTITYCREATEWINDOW_H
