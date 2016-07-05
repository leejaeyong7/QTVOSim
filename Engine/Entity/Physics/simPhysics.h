/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : simPhysics.h
 * @brief      : Entity physics definition file
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
#ifndef SIMPHYSICS_H
#define SIMPHYSICS_H
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <chrono>
#include "../simPrototype.h"
#include "../Math/simMath.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                                 NAMESPACES                                 //
//----------------------------------------------------------------------------//
using namespace std;
using namespace std::chrono;
using namespace JAE_MATH_FUNCTIONS;
//----------------------------------------------------------------------------//
//                               END NAMESPACES                               //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                              CLASS DEFINITION                              //
//----------------------------------------------------------------------------//
class SimPhysics
{
//----------------------------------------------------------------------------//
//                        PUBLIC FUNCTION DEFINITIONS                         //
//----------------------------------------------------------------------------//
public:
    /* default constructor */
    SimPhysics(Point3D position,
               array<double,3> rotation,
               bool gravity = false);
    /* default destructor */
    ~SimPhysics();

    /* copy constructor */
    SimPhysics(const SimPhysics& obj);

    /* assignment operator */
    SimPhysics& operator= (const SimPhysics& rhs);

    /* Updates position / rotation using velocity/acceleration */
    void update();
//----------------------------------------------------------------------------//
//                                  SETTERS                                   //
//----------------------------------------------------------------------------//
    /* Sets position of entity relative to parent (if exists) */
    void setPosition(double x, double y, double z);

    /* Sets position of entity using array of 3 doubles */
    void setPosition(Point3D p);

    /* Sets velocity of entity */
    void setVelocity(double a, double b, double c);

    /* Set velocity */
    void setVelocity(array<double,3> p);

    /* Sets acceleration of entity */
    void setAcceleration(double a, double b, double c);

    /* setRotation */
    void setAcceleration(array<double,3> p);

    /* Sets rotation of entity */
    void setRotation(double a, double b, double c);

    /* setRotation */
    void setRotation(array<double,3> p);

    /* Sets rot velocity of entity */
    void setAngVelocity(double a, double b, double c);

    /* setRot velocity */
    void setAngVelocity(array<double,3> p);

    /* Sets Rot accel of entity */
    void setAngAcceleration(double a, double b, double c);

    /* setRotation */
    void setAngAcceleration(array<double,3> p);

//----------------------------------------------------------------------------//
//                                  GETTERS                                   //
//----------------------------------------------------------------------------//
    /* Gets position of entity relative to parent */
    Point3D getPosition() const {return position;}

    /* Gets Velocity of entity */
    array<double,3> getVelocity() const {return velocity;}

    /* Gets Accleration of entity */
    array<double,3> getAcceleration() const {return acceleration;}

    /* Gets Rotation of entity */
    array<double,3> getRotation() const {return rotation;}

    /* Gets Angular Velocity of entity */
    array<double,3> getAngVelocity() const {return angVelocity;}

    /* Gets Angular Accleration of entity */
    array<double,3> getAngAcceleration() const {return angAcceleration;}
//----------------------------------------------------------------------------//
//                      END PUBLIC FUNCTION DEFINITIONS                       //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                       PRIVATE VARIABLE DECLARATIONS                        //
//----------------------------------------------------------------------------//
private:
    // translation coordinates
    Point3D position = {{0}};

    // velocity of entity
    array<double,3> velocity = {{0}};

    // acceleration of entity
    array<double,3> acceleration = {{0}};

    // rotation coordinates
    array<double,3> rotation = {{0}};

    // angular velocity
    array<double,3> angVelocity = {{0}};

    // angular acceleration
    array<double,3> angAcceleration = {{0}};

    // time parameter
    double time_start;

    // time holder
    double time_end;
//----------------------------------------------------------------------------//
//                     END PRIVATE VARIABLE DECLARATIONS                      //
//----------------------------------------------------------------------------//
};
//----------------------------------------------------------------------------//
//                           END CLASS DECLARATION                            //
//----------------------------------------------------------------------------//
#endif // SIMPHYSICS_H
