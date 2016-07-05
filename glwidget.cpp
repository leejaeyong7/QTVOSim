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
using namespace JAE_MATH_FUNCTIONS;
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
    entity = 0;
    editModeOn = false;
    setFocusPolicy(Qt::StrongFocus);
    setupEngine();
}

/**
 * @brief initializes opengl
 */
void GLWidget::initializeGL()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(16);

    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_MULTISAMPLE);
    glEnable( GL_POINT_SMOOTH);
    glPointSize(3);
}

/**
 * @brief draw event
 */
void GLWidget::paintGL()
{
    /* clear buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    GLdouble projectionMatrix[16];
    DSMat<4> projMat = engine->getCamera()->projectionMatrix();
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j< 4; j++)
        {
            projectionMatrix[i*4+j] = projMat[i][j];
        }
    }
    glLoadMatrixd(projectionMatrix);

    /* setup model / view matrix */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    setupLighting();
    /* update engine */
    engine->draw();
    engine->update();
    if(editModeOn)
    {
        updateEditEntity();
    }
    if(entity)
    {
        entity->update();
        entity->draw(engine->getCamera()->getInverseTransformation());
    }
    /* update gui */
    updateUI();
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLdouble xmin, xmax, ymin, ymax;

    ymax = zNear * tan( fovy * M_PI / 360.0 );
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;
    glFrustum( xmin, xmax, ymin, ymax, zNear, zFar );
}
/**
 * @brief sets up lighting
 */
void GLWidget::setupLighting()
{
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT,ambientColor);

    float no_mat[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[4] = {0.7f, 0.7f, 0.7f, 1.0f};
    float mat_diffuse[4]  = {0.1f, 0.5f, 0.8f, 1.0f};
    float mat_specular[4]  = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 5.0f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);

    //Add positioned light
    GLfloat lightColor0[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPos0[] = {0.0f, 0.0f, 50.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    GLfloat lightColor1[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPos1[] = {50.0f, 0.0f, 50.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
}
    

/**
 * @brief sets up engine
 */
void GLWidget::setupEngine()
{
    engine = new SimEngine(drawPoint,
                           drawLine,
                           drawTriangle,
                           drawRectangle,
                           drawSphere);
    SimCamera * mainCamera =
            new SimCamera("Default",0,0,10,0,0,0,60,90,1);
    engine->addEntity(mainCamera);
    engine->setCamera(mainCamera);
    SimRobot * robot1 =
            new SimRobot("robot1",0,0,0,0,0,0);
    SimGround * ground =
            new SimGround("ground",30,30,10);
    SimPlane * plane =
            new SimPlane("plane",5,5,3,0,0,0,2,3);
    engine->addEntity(ground);
    engine->addEntity(plane);
    engine->addEntity(robot1);
}
void GLWidget::updateUI()
{
    // update camera pos/rot
    Point3D p = engine->getCamera()->getPosition();
    array<double,3>r = engine->getCamera()->getRotation();
    QDoubleSpinBox* camPosX =
            window()->findChild<QDoubleSpinBox*>("cameraPosX");
    QDoubleSpinBox* camPosY =
            window()->findChild<QDoubleSpinBox*>("cameraPosY");
    QDoubleSpinBox* camPosZ =
            window()->findChild<QDoubleSpinBox*>("cameraPosZ");
    QDoubleSpinBox* camRotX =
            window()->findChild<QDoubleSpinBox*>("cameraRotX");
    QDoubleSpinBox* camRotY =
            window()->findChild<QDoubleSpinBox*>("cameraRotY");
    QDoubleSpinBox* camRotZ =
            window()->findChild<QDoubleSpinBox*>("cameraRotZ");

    if(!camPosX->hasFocus())
        camPosX->setValue(p[0]);
    if(!camPosY->hasFocus())
        camPosY->setValue(p[1]);
    if(!camPosZ->hasFocus())
        camPosZ->setValue(p[2]);

    if(!camRotX->hasFocus())
        camRotX->setValue(r[0]);
    if(!camRotY->hasFocus())
        camRotY->setValue(r[1]);
    if(!camRotZ->hasFocus())
        camRotZ->setValue(r[2]);

    if(entity && editModeOn)
    {
        QDoubleSpinBox* entPosX =
                        window()->findChild<QDoubleSpinBox*>("entityPosX");
        QDoubleSpinBox* entPosY =
                        window()->findChild<QDoubleSpinBox*>("entityPosY");
        QDoubleSpinBox* entPosZ =
                        window()->findChild<QDoubleSpinBox*>("entityPosZ");
        QDoubleSpinBox* entRotX =
                        window()->findChild<QDoubleSpinBox*>("entityRotX");
        QDoubleSpinBox* entRotY =
                        window()->findChild<QDoubleSpinBox*>("entityRotY");
        QDoubleSpinBox* entRotZ =
                        window()->findChild<QDoubleSpinBox*>("entityRotZ");
        Point3D p = entity->getPosition();
        array<double,3> r = entity->getRotation();
        if(!entPosX->hasFocus())
            entPosX->setValue(p[0]);
        if(!entPosY->hasFocus())
            entPosY->setValue(p[1]);
        if(!entPosZ->hasFocus())
            entPosZ->setValue(p[2]);

        if(!entRotX->hasFocus())
            entRotX->setValue(r[0]);
        if(!entRotY->hasFocus())
            entRotY->setValue(r[1]);
        if(!entRotZ->hasFocus())
            entRotZ->setValue(r[2]);
    }
}
void GLWidget::setEditEntity(SimEnvironment* ent)
{
    entity = ent;
    entity->getModel()->setPointDraw(drawPoint);
    entity->getModel()->setLineDraw(drawLine);
    entity->getModel()->setTriangleDraw(drawTriangle);
    entity->getModel()->setRectangleDraw(drawRectangle);
    entity->getModel()->setSphereDraw(drawSphere);
}

void GLWidget::setEditMode(bool mode)
{
    if(!mode)
    {
        editModeOn = false;
        return;
    }
    editModeOn = true;
    fixEntity = false;
}

/**
 * @brief updates edit entity(assumes that advoption already exists)
 */
void GLWidget::updateEditEntity()
{
    if(!entity)
    {
        return;
    }
    QLineEdit * name = window()->findChild<QLineEdit*>("entityName");
    QDoubleSpinBox * posX =
                    window()->findChild<QDoubleSpinBox*>("entityPosX");
    QDoubleSpinBox * posY =
                    window()->findChild<QDoubleSpinBox*>("entityPosY");
    QDoubleSpinBox * posZ =
                    window()->findChild<QDoubleSpinBox*>("entityPosZ");
    QDoubleSpinBox * rotX =
                    window()->findChild<QDoubleSpinBox*>("entityRotX");
    QDoubleSpinBox * rotY =
                    window()->findChild<QDoubleSpinBox*>("entityRotY");
    QDoubleSpinBox * rotZ =
                    window()->findChild<QDoubleSpinBox*>("entityRotZ");
    QTableWidget * advOptions =
                    window()->
                    findChild<QTableWidget*>("entityAdvancedOption");
    if(underMouse())
    {
        if(!fixEntity)
        {
            Point3D newPos = get3DMousePosition();
            entity->setPosition(newPos);
            posX->setValue(newPos[0]);
            posY->setValue(newPos[1]);
            posZ->setValue(newPos[2]);
        }
    }
    else
    {
        Point3D p = {{
                             posX->value(),
                             posY->value(),
                             posZ->value()
                     }};
        array<double,3> r = {{
                                     rotX->value(),
                                     rotY->value(),
                                     rotZ->value()
                             }};
        entity->setName(name->text().toStdString());
        entity->setPosition(p);
        entity->setRotation(r);
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
}
void GLWidget::clearEditEntityOptions()
{
    QLineEdit * name = window()->findChild<QLineEdit*>("entityName");
    QDoubleSpinBox * posX =
                    window()->findChild<QDoubleSpinBox*>("entityPosX");
    QDoubleSpinBox * posY =
                    window()->findChild<QDoubleSpinBox*>("entityPosY");
    QDoubleSpinBox * posZ =
                    window()->findChild<QDoubleSpinBox*>("entityPosZ");
    QDoubleSpinBox * rotX =
                    window()->findChild<QDoubleSpinBox*>("entityRotX");
    QDoubleSpinBox * rotY =
                    window()->findChild<QDoubleSpinBox*>("entityRotY");
    QDoubleSpinBox * rotZ =
                    window()->findChild<QDoubleSpinBox*>("entityRotZ");
    QTableWidget * advOptions =
                    window()->
                    findChild<QTableWidget*>("entityAdvancedOption");
    name->clear();
    posX->clear();
    posY->clear();
    posZ->clear();
    rotX->clear();
    rotY->clear();
    rotZ->clear();
    advOptions->clear();
}

void GLWidget::deleteEditEntity()
{
    clearEditEntityOptions();
    if(entity)
    {
        delete entity;
        entity = 0;
    }
}

Point3D GLWidget::get3DMousePosition()
{
    int height = this->height();
    int width = this->width();
    int xPos = width - this->mapFromGlobal(QCursor::pos()).x();
    int yPos = height - this->mapFromGlobal(QCursor::pos()).y();
    double x = (2.0f * xPos) / width - 1.0f;
    double y = 1.0f - (2.0f * yPos) / height;
    double z = 1.0f;
    Point3D pos = {{x,y,z}};
    Mat<double,4,1> homPos = toHomogenous(pos);

    DSMat<4>projection = engine->getCamera()->projectionMatrix();
    DSMat<4>transformation = engine->getCamera()->getTransformation();
    Mat<double,4,1> eye =  multiply<double,4,4,1>(
                inverse(projection),homPos);
    eye[2][0] = -1;
    eye[3][0] = 0;
    Mat<double,4,1>world = multiply<double,4,4,1>(transformation,eye);
    Point3D nworld = toPoint(normalize<4>(world));
    Point3D ret = {{0}};
    Point3D camPos = engine->getCamera()->getPosition();
    double t = -1*camPos[2]/nworld[2];
    ret[0] = (nworld[0]*t + camPos[0]);
    ret[1] = (nworld[1]*t + camPos[1]);


    return ret;
}

void GLWidget::placeEditEntity()
{
    engine->addEntity(entity);
    entity = 0;
    clearEditEntityOptions();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(!editModeOn)
    {
        lastPos = event->pos();
        lastButton = event->button();
    }
    else
    {
        if(event->button() == Qt::LeftButton)
        {
            fixEntity = !fixEntity;
        }
        else
        {
            deleteEditEntity();
        }
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(editModeOn)
    {
        return;
    }
    float dx = (event->pos().x()-lastPos.x());
    float dy = (event->pos().y()-lastPos.y());
    lastPos = event->pos();
    if(lastButton == Qt::LeftButton)
    {
        array<double,3> dr = {{dy*0.15, 0, dx*0.15}};
        array<double,3> r = engine->getCamera()->getRotation();
        engine->getCamera()->setRotation(tensor<3>(add,r,dr));
    }
    else if(lastButton == Qt::RightButton)
    {
        DSMat<4> p = engine->getCamera()->getTransformation();
        Point3D dp = {{-1*dx*0.03, dy*0.03, 0}};
        DSMat<4> translation = translationMatrix(dp);
        Point3D np = positionVector(multiply<4>(p,translation));
        engine->getCamera()->setPosition(np);
    }
}

//----------------------------------------------------------------------------//
//                      DRAWING STATIC HELPER FUNCTIONS                       //
//----------------------------------------------------------------------------//
void GLWidget::drawPoint(Point3D p)
{
    glBegin(GL_POINTS);
    glColor3d(1.0f,0,0);
    glVertex3d(p[0],p[1],p[2]);
    glEnd( );
    glColor3d(1.0,1.0,1.0);

}

void GLWidget::drawLine(Line l)
{
    glBegin(GL_LINES);
    for(int i = 0; i < 2; i++)
    {
        glVertex3d(l[i][0],l[i][1],l[i][2]);
    }
    glEnd();
}
void GLWidget::drawTriangle(Triangle t)
{

    Point3D p1 = t[0];
    Point3D p2 = t[1];
    Point3D p3 = t[2];

    array<double,3> u = tensor<3>(JAE_MATH_FUNCTIONS::minus,p2,p1);
    array<double,3> v = tensor<3>(JAE_MATH_FUNCTIONS::minus,p3,p1);

    Point3D normal = {{
                          u[1]*v[2] - u[2]*v[1],
                          u[2]*v[0] - u[0]*v[2],
                          u[0]*v[1] - u[1]*v[0]
                      }};

    glBegin(GL_TRIANGLES);
    glNormal3d(normal[0],normal[1],normal[2]);
    for(int i = 0; i < 3; i++)
    {
        glVertex3d(t[i][0],t[i][1],t[i][2]);
    }
    glEnd();
}
void GLWidget::drawRectangle(Rectangle r)
{

    Point3D p1 = r[0];
    Point3D p2 = r[1];
    Point3D p3 = r[2];

    array<double,3> u = tensor<3>(JAE_MATH_FUNCTIONS::minus,p2,p1);
    array<double,3> v = tensor<3>(JAE_MATH_FUNCTIONS::minus,p3,p1);

    Point3D normal = {{
                          u[1]*v[2] - u[2]*v[1],
                          u[2]*v[0] - u[0]*v[2],
                          u[0]*v[1] - u[1]*v[0]
                      }};

    glBegin(GL_QUADS);
    glNormal3d(normal[0],normal[1],normal[2]);
    for(int i = 0; i < 4; i++)
    {
        glVertex3d(r[i][0],r[i][1],r[i][2]);
    }
    glEnd();
}
void GLWidget::drawSphere(Sphere s)
{
    s.radius = 0;
}
