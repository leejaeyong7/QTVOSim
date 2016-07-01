/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : glwidget.cpp
 * @brief      : OpenGL qt widget definition file
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include "glwidget.h"
#include <iostream>
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
/**
 * @brief default widget constructor
 * @param parent parent widget
 * @return GLWidget object
 */
GLWidget::GLWidget(QWidget * parent):
    QOpenGLWidget(parent)
{
    engine = new SimEngine();
}

/**
 * @brief initializes opengl
 */
void GLWidget::initializeGL()
{
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}
/**
 * @brief draw event
 */
void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 * @brief resize event
 */
void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
}

/**
 * @brief sets view frustum using perspective params
 * @param fovy field of view y
 * @param aspect aspect ratio
 * @param zNear near value
 * @param zFar far value
 */
void GLWidget::perspective(GLdouble fovy, GLdouble aspect,
                           GLdouble zNear, GLdouble zFar)
{
    GLdouble xmin, xmax, ymin, ymax;

    ymax = zNear * tan( fovy * M_PI / 360.0 );
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustum( xmin, xmax, ymin, ymax, zNear, zFar );
}
