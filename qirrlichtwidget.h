#ifndef QIRRLICHTWIDGET_H
#define QIRRLICHTWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QResizeEvent>
#include <irrlicht.h>
#include "Engine/simEngine.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

// Our Irrlicht rendering widget

class QIrrlichtWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QIrrlichtWidget(QWidget *parent = 0);
    ~QIrrlichtWidget();

    // Returns a pointer to the Irrlicht Device
    IrrlichtDevice* getIrrlichtDevice();

    // Create the Irrlicht device and connect the signals and slots
    void init();

signals:
    // Signal that its time to update the frame
    void updateIrrlichtQuery(IrrlichtDevice* device);

public slots:
    // Function called in response to updateIrrlichtQuery. Renders the scene in the widget
    void updateIrrlicht(IrrlichtDevice* device);

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void timerEvent(QTimerEvent* event);
    virtual void resizeEvent(QResizeEvent* event);

    IrrlichtDevice *device;
    QWidget* renderWidget;
    // We keep the camera inside this widget so we can resize the window dynamically
    ICameraSceneNode* camera;
    SIrrlichtCreationParameters params;

    SimEngine * engine;
};

#endif // QIRRWIDGET_H
