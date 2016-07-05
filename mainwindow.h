/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : mainwindow.h
 * @brief      : main window function for qt5
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include <QMainWindow>
#include <glwidget.h>
#include <pathEditWindow.h>
#include <entityCreateWindow.h>
#include <entityEditWindow.h>
#include <QFileDialog>
#include <assimp/Importer.hpp>
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
/* forward declarartions */
class EntityCreateWindow;
class EntityEditWindow;
namespace Ui {
class MainWindow;
}
/* QT assertion */
Q_DECLARE_METATYPE(SimEntity*)
//----------------------------------------------------------------------------//
//                              CLASS DEFINITION                              //
//----------------------------------------------------------------------------//
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /* initializes main window */
    explicit MainWindow(QWidget *parent = 0);
    Ui::MainWindow * getUI(){return ui;}
    SimEngine * getEngine(){return glwidget->getEngine();}
    ~MainWindow();

    /* updates camera data */
    void setCameraPosX(double val);
    void setCameraPosY(double val);
    void setCameraPosZ(double val);
    void setCameraRotX(double val);
    void setCameraRotY(double val);
    void setCameraRotZ(double val);
    void updateCameraCombo();
    void setupEditEntity(int index);

    /* GUI functions */
private slots:
    void on_actionExit_triggered();

    void on_cameraPosX_valueChanged(double arg1);

    void on_cameraPosY_valueChanged(double arg1);

    void on_cameraPosZ_valueChanged(double arg1);

    void on_cameraRotX_valueChanged(double arg1);

    void on_cameraRotY_valueChanged(double arg1);

    void on_cameraRotZ_valueChanged(double arg1);

    void on_actionEntityAdd_triggered();

    void on_actionEntityEdit_triggered();

    void on_actionImport_triggered();

    void on_mainCameraSettingsButton_clicked();

    void on_mainCameraComboBox_currentIndexChanged(int index);

    void on_tabWidget_currentChanged(int index);

    void on_entityPlaceComboBox_currentIndexChanged(int index);

    void on_createEntityButton_clicked();

    void on_setEntityButton_clicked();

    void on_actionEditPath_triggered();

private:
    Ui::MainWindow *ui;
    /* opengl widget */
    GLWidget * glwidget;
    /* entity create window */
    EntityCreateWindow * entityCreateWindow;
    /* entity edit window */
    EntityEditWindow * entityEditWindow;
    PathEditWindow * pathEditWindow;
};
#endif // MAINWINDOW_H
//----------------------------------------------------------------------------//
//                            END CLASS DEFINITION                            //
//----------------------------------------------------------------------------//
