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
    Engine/Entity/Model/simModel.cpp

HEADERS  += mainwindow.h \
    Engine/simEngine.h \
    Engine/Entity/simEntity.h \
    Engine/Entity/simEntityOption.h \
    Engine/Entity/Robot/simRobot.h \
    glwidget.h \
    Engine/Entity/Physics/simPhysics.h \
    Engine/Entity/Sensor/simSensor.h \
    Engine/Entity/Model/simModel.h

FORMS    += mainwindow.ui
