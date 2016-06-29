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
    Engine/Physics/simPhysics.cpp

HEADERS  += mainwindow.h \
        qirrlichtwidget.h \
    Engine/simEngine.h \
    Engine/Entity/simEntity.h \
    Engine/Physics/simPhysics.h \
    Engine/Entity/simEntityOption.h

FORMS    += mainwindow.ui
