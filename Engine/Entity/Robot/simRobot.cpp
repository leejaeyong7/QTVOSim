/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : simRobot.cpp
 * @brief      : Robot entity definition file
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include "simRobot.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                              CLASS DEFINITION                              //
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

void SimRobot::update()
{
    SimEntity::update();
    getModel()->clear();
    //up
    //top left
    Point3D p1 = {{-0.5,-0.5,0.5}};
    //top right
    Point3D p2 = {{0.5,-0.5,0.5}};
    //bot right /front
    Point3D p3 = {{0.5,0.5,0.5}};
    // bot left /front
    Point3D p4 = {{-0.5,0.5,0.5}};
    // down
    //top left
    Point3D p5 = {{-0.5,-0.5,0}};
    //top right
    Point3D p6 = {{0.5,-0.5,0}};
    //bot right /front
    Point3D p7 = {{0.5,0.5,0}};
    // bot left /front
    Point3D p8 = {{-0.5,0.5,0}};

    // ul ur dr rl
    //up
    Rectangle r1 = {{p1,p2,p3,p4}};
    //front
    Rectangle r2 = {{p4,p3,p7,p8}};
    //left
    Rectangle r3 = {{p1,p4,p8,p5}};
    //right
    Rectangle r4 = {{p3,p2,p6,p7}};
    //back
    Rectangle r5 = {{p2,p1,p5,p6}};
    //down
    Rectangle r6 = {{p8,p7,p6,p5}};

    getModel()->addRectangle(r1);
    getModel()->addRectangle(r2);
    getModel()->addRectangle(r3);
    getModel()->addRectangle(r4);
    getModel()->addRectangle(r5);
    getModel()->addRectangle(r6);
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
//----------------------------------------------------------------------------//
//                            END CLASS DEFINITION                            //
//----------------------------------------------------------------------------//
