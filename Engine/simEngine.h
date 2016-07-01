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

    /**
     * Constructor
     * Initialize Irrlicht, Entities, and physics
     * @param bool - if true, setup GUI
     */
    SimEngine();

    /**
     * @brief updates engine
     */
    void update();

    /**
     * Runs Simulation with physics, environment, and 3D rendering
     */
    void run();

    /**
     * fetch pointer to entity vector
     * @return pointer to vector of enitty pointers
     */
    vector<SimEntity*> * getEntityVector(){return &simEntityVector;}

    /**
     * fetch pointer to entity searched by name
     * @param string - name
     * @return SimEntity * - pointer to entity object
     */
    SimEntity* getEntityByName(std::string name);

    /**
     * adds entity to rendering
     * @param EntityType - type of entity object to add
     * @param SimEntity - entity object to add
     * @see SimEntity
     * @return None
     */
    void addEntity(SimEntity * obj);

    /**
     * removes entity object from rendering
     * if entity object doesn't exist, it will do nothing
     * @param SimEntity - pointer to entity object to remove
     * @return None
     */
    void removeEntity(SimEntity * obj);

private:
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
