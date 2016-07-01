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
#define PI 3.1415926535
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                                 NAMESPACES                                 //
//----------------------------------------------------------------------------//
using namespace std;
using namespace std::chrono;
//----------------------------------------------------------------------------//
//                               END NAMESPACES                               //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                            TYPEDEF DEFINITIONS                             //
//----------------------------------------------------------------------------//
typedef array<double,3> Point3D;
typedef array<double,2> Point2D;
typedef array<Point3D,2> Line;
typedef array<Point3D,3> Triangle;
typedef array<Point3D,4> Rectangle;
typedef struct Sphere
{
    Point3D center;
    double radius;
}Sphere;
typedef double (*fun_1)(double a);
typedef double (*fun_2)(double a,double b);
//----------------------------------------------------------------------------//
//                          END TYPEDEF DEFINITIONS                           //
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
    // maps points
    array<double,3> map(fun_2 func,array<double,3> orig, double param);

    // apply points
    array<double,3> apply(fun_1 func,array<double,3> orig);

    // tensor points
    array<double,3> tensor(fun_2 func,array<double,3> p1, array<double,3> p2);

    // translation coordinates
    Point3D position;

    // velocity of entity
    array<double,3> velocity;

    // acceleration of entity
    array<double,3> acceleration;

    // rotation coordinates
    array<double,3> rotation;

    // angular velocity
    array<double,3> angVelocity;

    // angular acceleration
    array<double,3> angAcceleration;

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
