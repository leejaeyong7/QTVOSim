#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QOpenGLWidget>
#include <GL/glext.h>
#include <GL/glu.h>
#include "Engine/simEngine.h"
class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget * parent =  0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
private:
    SimEngine * engine;
};

#endif // GLWIDGET_H
