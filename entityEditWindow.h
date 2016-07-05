/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : editEntityWindow.h
 * @brief      : declaration file for entity edit window
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
#ifndef ENTITYEDITWINDOW_H
#define ENTITYEDITWINDOW_H
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include "mainwindow.h"
#include "Engine/simEntityList.h"
#include <QDialog>
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
class MainWindow;
namespace Ui {
class EntityEditWindow;
}
//----------------------------------------------------------------------------//
//                             CLASS DECLARATION                              //
//----------------------------------------------------------------------------//
class EntityEditWindow: public QDialog
{
    Q_OBJECT

public:
    explicit EntityEditWindow(QWidget *parent = 0);
    ~EntityEditWindow();

    /* opens menu given entity */
    void openMenu(SimEntity* entity);

private slots:
    void on_robotComboBox_currentIndexChanged(int index);

    void on_sensorComboBox_currentIndexChanged(int index);

    void on_environmentComboBox_currentIndexChanged(int index);

    void on_deleteButton_clicked();

    void on_editEntityTab_currentChanged(int index);

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

    /* sets up combo box */
    void setupCombo(int index);
    /* loads entity on GUI */
    void loadEntity(int index);
    /* updates entity */
    void updateEntity();
    SimEntity* entity;

    Ui::EntityEditWindow*ui;
};
//----------------------------------------------------------------------------//
//                           END CLASS DECLARATION                            //
//----------------------------------------------------------------------------//
#endif // EDITENTITYWINDOW_H
