/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : simEngine.h
 * @brief      : Simulator Engine declaration file
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
#ifndef _SIM_ENGINE_H_
#define _SIM_ENGINE_H_
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include "Entity/simEntity.h"
#include "simEntityList.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                                NAME SPACES                                 //
//----------------------------------------------------------------------------//
using namespace std;
//----------------------------------------------------------------------------//
//                              END NAME SPACES                               //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                             CLASS DECLARATION                              //
//----------------------------------------------------------------------------//
class SimEngine
{
public:

    /* Default Constructor */
    SimEngine(pointDraw pointDrawFunc = 0,
              lineDraw lineDrawFunc = 0,
              triangleDraw triangleDrawFunc = 0,
              rectangleDraw rectangleDrawFunc = 0,
              sphereDraw sphereDrawFunc = 0);

    /* default destructor */
    ~SimEngine();

    /* updates engine */
    void update();

    /* draws all entities */
    void draw();

    /* Runs Simulation with physics, environment, and 3D rendering */
    void run();

    /* sets default camera */
    void setCamera(SimCamera * cam);

    /* gets MainCamera */
    SimCamera* getCamera();

    /* fetch pointer to entity vector */
    vector<SimEntity*> * getEntityVector(){return &simEntityVector;}

    /* fetch pointer to entity searched by name */
    SimEntity* getEntityByName(std::string name);

    /* adds entity to rendering */
    void addEntity(SimEntity * obj);

    /* removes entity object from rendering */
    void removeEntity(SimEntity * obj);

private:
    // main camera ptr
    SimCamera * mainCamera;
    // default model for all objects
    SimModel * defaultModel;
    SimModel * getDefaultModel(){return defaultModel;}

    // vector of SimEntity object
    vector<SimEntity*> simEntityVector;

    //functor for find_if predicate
    struct checkEntityName
    {
        checkEntityName(const std::string name) : name_holder(name) {}
        std::string name_holder;
        bool operator()(SimEntity* obj)
        {
            return obj->getName().compare(name_holder) == 0;
        }
    };
};
#endif
//----------------------------------------------------------------------------//
//                           END CLASS DECLARATION                            //
//----------------------------------------------------------------------------//
