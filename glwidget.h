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
#include <QOpenGLWidget>
#include "Engine/simEngine.h"
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

private:
    // holds entity engine
    SimEngine * engine;

    // sets view frustum using perspective camera
    void perspective(GLdouble fovy, GLdouble aspect,
                     GLdouble zNear, GLdouble zFar);
};
#endif // GLWIDGET_H
//----------------------------------------------------------------------------//
//                           END CLASS DECLARATION                            //
//----------------------------------------------------------------------------//
