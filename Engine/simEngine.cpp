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
SimEngine::SimEngine()
{

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
 * @brief runs engine in while loop
 */
void SimEngine::run()
{
    while(1)
    {
        update();
    }
    return;
}
//----------------------------------------------------------------------------//
//                            END CLASS DEFINITION                            //
//----------------------------------------------------------------------------//
