/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : glwidget.h
 * @brief      : OpenGL qt widget definition file
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
#ifndef GLWIDGET_H
#define GLWIDGET_H
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include <iostream>
#include <QDoubleSpinBox>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QTimer>
#include <QComboBox>
#include <QTableWidget>
#include <QLineEdit>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Engine/simEngine.h"
#include "Engine/simEntityList.h"
#include "Engine/Entity/Math/simMath.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                             CLASS DECLARATION                              //
//----------------------------------------------------------------------------//
class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    /* default constructor */
    explicit GLWidget(QWidget * parent =  0);

    /* initializes opengl context */
    void initializeGL();

    /* draw event */
    void paintGL();

    /* resize event */
    void resizeGL(int w, int h);

    /* updates UI */
    void updateUI();

    /* sets up opengl lighting */
    void setupLighting();

    /* sets up engine */
    void setupEngine();

    /* gets engine object */
    SimEngine * getEngine(){return engine;}


    /* sets edit mode */
    void setEditMode(bool mode);

    /* sets current environment entity(in place mode) */
    void setEditEntity(SimEnvironment * ent);

    /* fetch edit entity */
    SimEnvironment * getEditEntity(){return entity;}

    /* deletes edit entity */
    void clearEditEntityOptions();
    void deleteEditEntity();

    void placeEditEntity();


    /* opengl mouse event handler */
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    /* sets view frustum using perspective camera */
    void perspective(GLdouble fovy, GLdouble aspect,
                     GLdouble zNear, GLdouble zFar);

    /* updates edit entity */
    void updateEditEntity();

    Point3D get3DMousePosition();


    /* holds entity engine */
    SimEngine * engine;
    SimEnvironment * entity;

    /* holds mouse button data */
    QPoint lastPos;
    Qt::MouseButton lastButton;

    /* true if edit place mode is on */
    bool editModeOn;
    bool fixEntity;

    /* static draw functions for engine */
    static void drawPoint(Point3D p);
    static void drawLine(Line l);
    static void drawTriangle(Triangle t);
    static void drawRectangle(Rectangle r);
    static void drawSphere(Sphere s);

};
#endif // GLWIDGET_H
//----------------------------------------------------------------------------//
//                           END CLASS DECLARATION                            //
//----------------------------------------------------------------------------//
