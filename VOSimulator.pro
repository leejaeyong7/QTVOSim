#-------------------------------------------------
#
# Project created by QtCreator 2016-06-28T21:22:06
#
#-------------------------------------------------

QT       += core gui opengl widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VOSimulator
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    Engine/simEngine.cpp \
    Engine/Entity/simEntity.cpp \
    Engine/Entity/Robot/simRobot.cpp \
    glwidget.cpp \
    Engine/Entity/Physics/simPhysics.cpp \
    Engine/Entity/Sensor/simSensor.cpp \
    Engine/Entity/Model/simModel.cpp \
    Engine/Entity/Sensor/simCamera.cpp \
    Engine/Entity/Math/simMath.cpp \
    Engine/Entity/Environment/simenvironment.cpp \
    entityCreateWindow.cpp \
    Engine/Entity/Environment/simGround.cpp \
    Engine/Entity/Environment/simPlane.cpp \
    entityEditWindow.cpp \
    pathEditWindow.cpp

HEADERS  += mainwindow.h \
    Engine/simEngine.h \
    Engine/Entity/simEntity.h \
    Engine/Entity/simEntityOption.h \
    Engine/Entity/Robot/simRobot.h \
    glwidget.h \
    Engine/Entity/Physics/simPhysics.h \
    Engine/Entity/Sensor/simSensor.h \
    Engine/Entity/Model/simModel.h \
    Engine/Entity/simPrototype.h \
    Engine/Entity/Sensor/simCamera.h \
    Engine/simEntityList.h \
    Engine/Entity/Math/simMath.h \
    Engine/Entity/Environment/simenvironment.h \
    entityCreateWindow.h \
    Engine/Entity/Environment/simGround.h \
    Engine/Entity/Environment/simPlane.h \
    entityEditWindow.h \
    pathEditWindow.h

FORMS    += mainwindow.ui \
    entityCreateWindow.ui \
    entityEditWindow.ui \
    pathEditWindow.ui
