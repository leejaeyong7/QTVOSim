/*============================================================================
 * @author: Jae Yong Lee
 * @file: simRobot.cpp
 * @version:
 * @summary:
 *      Definition file for sim robot objects
 *
 *============================================================================*/
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include "simRobot.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                                DEFINITIONS                                 //
//----------------------------------------------------------------------------//
/**
 * @brief Constructor with position/rotation
 * @param _name - name of entity
 * @param x  x axis coordinate
 * @param y  y axis coordinate
 * @param z  z axis coordinate
 * @param a  roll
 * @param b  pitch
 * @param c  yaw
 * @param parent parent entity
 * @return SimRobot object
 */
SimRobot::SimRobot(string _name,
                   double x, double y, double z,
                   double a, double b, double c, SimEntity* parent)
    :SimEntity(_name,x,y,z,a,b,c,parent)
{

}

/**
 * Default Destructor
 * Removes sensors attached to robot
 */
SimRobot::~SimRobot()
{
    vector<SimSensor*>::iterator it;
    for(it = sensorVector.begin() ; it < sensorVector.end(); ++it)
    {
        (*it)->setParent(0);
    }
}
/**
 * Adds Sensor to robot
 * @param SimSensor* - pointer to sensor object to add
 * @return None
 */
void SimRobot::addSensor(SimSensor* obj)
{
    if(!obj)
        return;
    sensorVector.push_back(obj);
    obj->setParent(this);
}

/**
 * Remove Sensor to robot
 * @param SimSensor* - pointer to sensor object to remove
 * @return None
 */
void SimRobot::removeSensor(SimSensor* obj)
{
    if(!obj)
        return;
    if(obj->getParent() != this)
        return;
    sensorVector.erase(
        std::remove(sensorVector.begin(),
                    sensorVector.end(),
                    obj),
        sensorVector.end());
    obj->setParent(0);
}
