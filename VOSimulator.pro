#-------------------------------------------------
#
# Project created by QtCreator 2016-06-28T21:22:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VOSimulator
TEMPLATE = app
LIBS += -lIrrlicht
INCLUDEPATH += /usr/include/irrlicht/

SOURCES += main.cpp\
        mainwindow.cpp \
        qirrlichtwidget.cpp \
    Engine/simEngine.cpp \
    Engine/Entity/simEntity.cpp \
    Engine/Physics/simPhysics.cpp \
    Engine/Entity/Sensor/simCamera.cpp \
    Engine/Entity/Robot/simRobot.cpp \
    Engine/Entity/Environment/simEnvironment.cpp \
    Engine/Entity/Sensor/simSensor.cpp \
    Engine/Entity/Environment/simPlane.cpp

HEADERS  += mainwindow.h \
        qirrlichtwidget.h \
    Engine/simEngine.h \
    Engine/Entity/simEntity.h \
    Engine/Physics/simPhysics.h \
    Engine/Entity/simEntityOption.h \
    Engine/Entity/Sensor/simCamera.h \
    Engine/Entity/Robot/simRobot.h \
    Engine/Entity/Environment/simEnvironment.h \
    Engine/Entity/Sensor/simSensor.h \
    Engine/Entity/Environment/simPlane.h

FORMS    += mainwindow.ui
