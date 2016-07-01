#include "simPhysics.h"
namespace JAE_MATH_FUNCTIONS{
double add(double a, double b)
{
    return a+b;
}

double multiply(double a, double b)
{
    return a*b;
}

double over(double a, double b)
{
    return (a>b) ? a : b-a;
}

double less(double a, double b)
{
    return (a < b) ? a : a - b;
}

double toDeg(double rad)
{
    return rad * 180.0 / PI;
}

double toRad(double deg)
{
    return deg * PI / 180.0;
}

double fitDeg(double deg)
{
    return less(over(deg,0),360);
}

double fitRad(double rad)
{
    return less(over(rad,0),2*PI);
}
}
using namespace JAE_MATH_FUNCTIONS;
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
    position = tensor(add,position,map(multiply,velocity,ms));
    velocity = tensor(add,velocity,map(multiply,acceleration,ms));
    rotation = apply(fitDeg,(tensor(add,rotation,map(multiply,velocity,ms))));
    angVelocity = apply(fitDeg,(tensor(add,velocity,map(multiply,acceleration,ms))));
}


/**
 * @brief SimPhysics::map
 * @param orig original point
 * @param param parameter to be used
 * @param func funtion to apply that takes two variables
 * @return array with map operation of func
 */
array<double,3> SimPhysics::map(fun_2 func,array<double,3> orig, double param)
{
    array<double,3> ret;
    ret[0] = func(orig[0],param);
    ret[1] = func(orig[1],param);
    ret[2] = func(orig[2],param);
    return ret;
}

/**
 * @brief SimPhysics::apply
 * @param p1 point1
 * @param func function that takes one variables
 * @return array with func applied to each element
 */
array<double,3> SimPhysics::apply(fun_1 func,array<double,3> orig)
{
    array<double,3> ret;
    ret[0] = func(orig[0]);
    ret[1] = func(orig[1]);
    ret[2] = func(orig[2]);
    return ret;
}

/**
 * @brief SimPhysics::tensor
 * @param p1 point1
 * @param p2 point 2
 * @param func function that takes two variables
 * @return array with tensor operation of func
 */
array<double,3> SimPhysics::tensor(fun_2 func,array<double,3> p1, array<double,3> p2)
{
    array<double,3> ret;
    ret[0] = func(p1[0],p2[0]);
    ret[1] = func(p1[1],p2[1]);
    ret[2] = func(p1[2],p2[2]);
    return ret;
}
