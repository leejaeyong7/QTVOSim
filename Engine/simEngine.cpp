/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : simEngine.cpp
 * @brief      : Simulator Engine definition file
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include "simEngine.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                              CLASS DEFINITION                              //
//----------------------------------------------------------------------------//
/**
 * @brief default constructor
 */
SimEngine::SimEngine(pointDraw pointDrawFunc,
                     lineDraw lineDrawFunc,
                     triangleDraw triangleDrawFunc,
                     rectangleDraw rectangleDrawFunc,
                     sphereDraw sphereDrawFunc)
{
    defaultModel = new SimModel();
    defaultModel->setPointDraw(pointDrawFunc);
    defaultModel->setLineDraw(lineDrawFunc);
    defaultModel->setTriangleDraw(triangleDrawFunc);
    defaultModel->setRectangleDraw(rectangleDrawFunc);
    defaultModel->setSphereDraw(sphereDrawFunc);
    mainCamera = 0;
}

/**
 * @brief default destructor
 */
SimEngine::~SimEngine()
{
    std::vector<SimEntity*>::iterator it;
    for(it = simEntityVector.begin();
        it != simEntityVector.end();
        it++)
    {
        delete (*it);
    }
    delete defaultModel;
}

/**
 * @brief updates engine and entities
 */
void SimEngine::update()
{
    std::vector<SimEntity*>::iterator it;
    for(it = simEntityVector.begin();
        it != simEntityVector.end();
        it++)
    {
        (*it)->update();
    }
}

/**
 * @brief draws all entity
 */
void SimEngine::draw()
{
    // calculate cameram view matrix
    if(!getCamera())
    {
        return;
    }
    DSMat<4> ViewMat = getCamera()->getInverseTransformation();
    std::vector<SimEntity*>::iterator it;
    for(it = simEntityVector.begin();
        it != simEntityVector.end();
        it++)
    {
        if(*it != getCamera())
        {
            (*it)->draw(ViewMat);
        }
    }
}

/**
 * @brief runs engine in while loop
 */
void SimEngine::run()
{
    while(1)
    {
        update();
        draw();
    }
    return;
}

/**
 * @brief sets default camera for engine(can be NULL)
 * @param cam camera to set
 */
void SimEngine::setCamera(SimCamera *cam)
{
    mainCamera = cam;
}


/**
 * @brief gets default camera for engine(can be NULL);
 */
SimCamera* SimEngine::getCamera()
{
    return mainCamera;
}

/**
 * @brief adds entity to engine
 * @param obj entity to add
 */
void SimEngine::addEntity(SimEntity * obj)
{
    if(!obj)
    {
        return;
    }
    obj->getModel()->setPointDraw(defaultModel->getPointDraw());
    obj->getModel()->setLineDraw(defaultModel->getLineDraw());
    obj->getModel()->setTriangleDraw(defaultModel->getTriangleDraw());
    obj->getModel()->setRectangleDraw(defaultModel->getRectangleDraw());
    obj->getModel()->setSphereDraw(defaultModel->getSphereDraw());
    simEntityVector.push_back(obj);
}

/**
 * @brief removes entity from engine
 * @param obj entity to remove
 */
void SimEngine::removeEntity(SimEntity * obj)
{
    if(!obj)
        return;
    if(obj == getCamera())
        return;
    simEntityVector.erase(
        std::remove(simEntityVector.begin(),
                    simEntityVector.end(),
                    obj),
        simEntityVector.end());
}


/**
 * @brief search entity by it's name
 */
SimEntity* SimEngine::getEntityByName(std::string name)
{
    std::vector<SimEntity*>::iterator it;

    it = std::find_if(
        simEntityVector.begin(),
        simEntityVector.end(),
        checkEntityName(name)
        );
    if (it != simEntityVector.end())
        return (*it);
    else
        return 0;
}
//----------------------------------------------------------------------------//
//                            END CLASS DEFINITION                            //
//----------------------------------------------------------------------------//
