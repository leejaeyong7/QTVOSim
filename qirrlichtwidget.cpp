#include "qirrlichtwidget.h"
#include <iostream>
using namespace std;
QIrrlichtWidget::QIrrlichtWidget(QWidget *parent) :
    QWidget(parent)
{
    device = 0;
    renderWidget= parent;
    engine = new SimEngine();
}

QIrrlichtWidget::~QIrrlichtWidget()
{
    if(device != 0)
    {
        device->closeDevice();
        device->drop();
    }
}

// Create the Irrlicht device and connect the signals and slots
void QIrrlichtWidget::init()
{
    // Make sure we can't create the device twice
    if(device != 0)
        return;

    // Set all the device creation parameters
    SIrrlichtCreationParameters params;
    params.AntiAlias = 0;
    params.Bits = 32;
    params.DeviceType = EIDT_X11;
    params.Doublebuffer = true;
    params.DriverType = EDT_BURNINGSVIDEO;//EDT_OPENGL;
    params.EventReceiver = 0;
    params.Fullscreen = false;
    params.HighPrecisionFPU = false;
    params.IgnoreInput = false;
    params.LoggingLevel = ELL_INFORMATION;
    params.Stencilbuffer = true;
    params.Stereobuffer = false;
    params.Vsync = false;
    // Specify which window/widget to render to
    params.WindowId = reinterpret_cast<void*>(renderWidget->winId());
    params.WindowSize.Width = renderWidget->width();
    params.WindowSize.Height = renderWidget->height();
    params.WithAlphaChannel = false;
    params.ZBufferBits = 16;
    // Create the Irrlicht Device with the previously specified parameters
    device = createDeviceEx(params);

    if(device)
    {
        // Create a camera so we can view the scene
        camera = device->getSceneManager()->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
    }
    setGeometry(0,
                0,
                device->getVideoDriver()->getCurrentRenderTargetSize().Width,
                device->getVideoDriver()->getCurrentRenderTargetSize().Height
                );

    // Connect the update signal (updateIrrlichtQuery) to the update slot (updateIrrlicht)
    connect (this, &QIrrlichtWidget::updateIrrlichtQuery, this, &QIrrlichtWidget::updateIrrlicht);

    // Start a timer. A timer with setting 0 will update as often as possible.
    startTimer(0);
}

IrrlichtDevice* QIrrlichtWidget::getIrrlichtDevice()
{
    return device;
}

void QIrrlichtWidget::paintEvent(QPaintEvent* event)
{
    if(device != 0)
    {
        emit updateIrrlichtQuery(device);
    }

    event->accept();
}

void QIrrlichtWidget::timerEvent(QTimerEvent* event)
{
    // Emit the render signal each time the timer goes off
    if (device != 0)
    {
        emit updateIrrlichtQuery(device);
    }

    event->accept();
}

void QIrrlichtWidget::resizeEvent(QResizeEvent* event)
{
    if(device != 0)
    {
        dimension2d<u32> widgetSize;
        widgetSize.Width = event->size().width();
        widgetSize.Height = event->size().height();
        device->getVideoDriver()->OnResize(widgetSize);

        ICameraSceneNode *cam = device->getSceneManager()->getActiveCamera();
        if (cam != 0)
        {
            cam->setAspectRatio((f32)widgetSize.Width / (f32)widgetSize.Height);
        }
    }
}

void QIrrlichtWidget::updateIrrlicht( irr::IrrlichtDevice* device )
{
    if(device != 0)
    {
        device->getTimer()->tick();

        SColor color (0,0,0,0);
        device->getVideoDriver()->beginScene(true, true, color);
        device->getSceneManager()->drawAll();
        device->getVideoDriver()->endScene();
        engine->run();
    }
}
