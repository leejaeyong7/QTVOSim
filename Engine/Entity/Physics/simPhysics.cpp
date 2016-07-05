/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : simPhysics.cpp
 * @brief      : Entity physics definition file
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include "simPhysics.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                              CLASS DEFINITION                              //
//----------------------------------------------------------------------------//
/**
 * @brief default constructor for physics
 * @param position position of entity
 * @param rotation position of entity
 * @param gravity apply gravity(default false);
 */
SimPhysics::SimPhysics(Point3D position,
                       array<double,3> rotation,
                       bool gravity)
{
    auto now = system_clock::now();
    auto now_ms = time_point_cast<milliseconds>(now);
    auto value = now_ms.time_since_epoch();
    time_start = (double)(value.count());
    this->position = position;
    this->rotation = rotation;
}

/**
 * @brief copy constructor
 * @param obj object to be copied from
 */
SimPhysics::SimPhysics(const SimPhysics &obj)
{
    position = obj.getPosition();
    rotation = obj.getRotation();
    velocity = obj.getVelocity();
    acceleration = obj.getAcceleration();
    angVelocity = obj.getAngVelocity();
    angAcceleration = obj.getAngAcceleration();
    auto now = system_clock::now();
    auto now_ms = time_point_cast<milliseconds>(now);
    auto value = now_ms.time_since_epoch();
    time_start = (double)(value.count());
}

/**
 * @brief assignment operator
 * @param rhs object to be copied from
 */
SimPhysics& SimPhysics::operator=(const SimPhysics& rhs)
{
    position = rhs.getPosition();
    rotation = rhs.getRotation();
    velocity = rhs.getVelocity();
    acceleration = rhs.getAcceleration();
    angVelocity = rhs.getAngVelocity();
    angAcceleration = rhs.getAngAcceleration();
    auto now = system_clock::now();
    auto now_ms = time_point_cast<milliseconds>(now);
    auto value = now_ms.time_since_epoch();
    time_start = (double)(value.count());
    return *this;
}
SimPhysics::~SimPhysics()
{
    return;
}

/**
 * @brief updates physical properties
 */
void SimPhysics::update()
{
    auto now = system_clock::now();
    auto now_ms = time_point_cast<milliseconds>(now);
    auto value = now_ms.time_since_epoch();
    time_end = (double)(value.count());
    double ms = (time_end - time_start);
    time_start = time_end;
    position = tensor<3>(add,
                         position,
                         map<3>(multiply,velocity,ms));
    velocity = tensor<3>(add,
                         velocity,
                         map<3>(multiply,acceleration,ms));
    rotation = apply<3>(fitDeg,
                        (tensor<3>(add,
                                   rotation,
                                   map<3>(multiply,velocity,ms))));
    angVelocity = apply<3>(fitDeg,
                           (tensor<3>(add,
                                      velocity,
                                      map<3>(multiply,acceleration,ms))));
}

/**
 * @brief Sets position of entity relative to parent(if exists)
 * @param x axis coord
 * @param y axis coord
 * @param z axis coord
 */
void SimPhysics::setPosition(double x, double y, double z)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

/**
 * @brief setPosition
 * @param p position to set
 */
void SimPhysics::setPosition(Point3D p)
{
    position = p;
}


void SimPhysics::setVelocity(double a, double b, double c)
{
    velocity[0] = a;
    velocity[1] = b;
    velocity[2] = c;
}
void SimPhysics::setVelocity(array<double,3> p)
{
    velocity = p;
}


void SimPhysics::setAcceleration(double a, double b, double c)
{
    acceleration[0] = a;
    acceleration[1] = b;
    acceleration[2] = c;
}
void SimPhysics::setAcceleration(array<double,3> p)
{
    acceleration = p;
}


/**
 * @brief Sets rotation of entity
 * @param a roll
 * @param b pitch
 * @param c yaw
 */
void SimPhysics::setRotation(double a, double b, double c)
{
    rotation[0] = a;
    rotation[1] = b;
    rotation[2] = c;
}

/**
 * @brief setRotation
 * @param p position to set
 */
void SimPhysics::setRotation(array<double,3> p)
{
    rotation = p;
}


void SimPhysics::setAngVelocity(double a, double b, double c)
{
    angVelocity[0] = a;
    angVelocity[1] = b;
    angVelocity[2] = c;
}
void SimPhysics::setAngVelocity(array<double,3> p)
{
    angVelocity = p;
}


void SimPhysics::setAngAcceleration(double a, double b, double c)
{
    angAcceleration[0] = a;
    angAcceleration[1] = b;
    angAcceleration[2] = c;
}
void SimPhysics::setAngAcceleration(array<double,3> p)
{
    angAcceleration = p;
}
//----------------------------------------------------------------------------//
//                            END CLASS DEFINITION                            //
//----------------------------------------------------------------------------//
