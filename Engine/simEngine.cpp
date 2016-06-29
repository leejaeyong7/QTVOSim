/*============================================================================
 * @author: Jae Yong Lee
 * @file: simEngine.cpp
 * @version:
 * @summary:
 *      Definition file for simulation engine
 *
 *============================================================================*/
//----------------------------------------------------------------------------//
//                                  Includes
//----------------------------------------------------------------------------//
#include "simEngine.h"
//----------------------------------------------------------------------------//
//                               Class Definitions
//----------------------------------------------------------------------------//

SimEngine::SimEngine()
{
    simPhysics = new SimPhysics();
}

void SimEngine::addEntity(SimEntity * obj)
{
    if(!obj)
    {
        return;
    }
    simEntityVector.push_back(obj);
}

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

void SimEngine::run()
{
    return;
}
