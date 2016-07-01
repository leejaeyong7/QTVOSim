/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : simEntity.cpp
 * @brief      : Entity definition file
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include "simEntity.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                         HELPER FUNCTION DENITIONS                          //
//----------------------------------------------------------------------------//
double radToDeg(double rad)
{
    return rad*180.0/PI;
}

double degToRad(double deg)
{
    return deg*PI/180.0;
}

array<double,9> eul2mat(array<double,3> rot)
{
    array<double,9> rotmat;

    double a = degToRad(rot[0]);
    double b = degToRad(rot[1]);
    double c = degToRad(rot[2]);

    rotmat[0] = cos(b)*cos(c);
    rotmat[1] = sin(a)*sin(b)*cos(c) + cos(a)*sin(c);
    rotmat[2] = -1*cos(a)*sin(b)*cos(c) + sin(a)*sin(c);

    rotmat[3] = -1*cos(b)*cos(c);
    rotmat[4] = -1*sin(a)*sin(b)*sin(c) + cos(a)*cos(c);
    rotmat[5] = cos(a)*sin(b)*sin(c) + sin(a)*cos(c);

    rotmat[6] = sin(b);
    rotmat[7] = -1*sin(a)*cos(b);
    rotmat[8] = cos(a)*cos(b);
    return rotmat;
}
array<double,3> add(Point3D p1,Point3D p2)
{
    array<double,3> ret;
    ret[0] = p1[0] + p2[0];
    ret[1] = p1[1] + p2[1];
    ret[2] = p1[2] + p2[2];
    return ret;
}

array<double,3> rotate(Point3D p, array<double,3> rot)
{
    array<double,9> rotmat = eul2mat(rot);
    array<double,3> rotated;
    rotated[0] = rotmat[0]*p[0] + rotmat[1]*p[1]+rotmat[2]*p[2];
    rotated[1] = rotmat[3]*p[0] + rotmat[4]*p[1]+rotmat[5]*p[2];
    rotated[2] = rotmat[6]*p[0] + rotmat[7]*p[1]+rotmat[8]*p[2];
    return rotated;
}
//----------------------------------------------------------------------------//
//                       END HELPER FUNCTION DENITIONS                        //
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
 * @return SimEntity object
 */
SimEntity::SimEntity(string _name,
                     double x, double y, double z,
                     double a, double b, double c, SimEntity *parent)
{
    setName(_name);
    setParent(parent);
    array<double,3> pos;
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    array<double,3> rot;
    rot[0] = a;
    rot[1] = b;
    rot[2] = c;
    physics = new SimPhysics(pos,rot);
}


/**
 * Copy Constructor
 * @param SimEntity - SimEntity Object to copy from
 * @return Copied SimEntity object
 */
SimEntity::SimEntity(const SimEntity & obj)
{
    setName(obj.getName());
    setParent(obj.getParent());
    physics = new SimPhysics(*(obj.getPhysics()));
    advancedOption = *(obj.getAdvancedOption());
    points = *(obj.getPoints());
    triangles = *(obj.getTriangles());
    rectangles = *(obj.getRectangles());
    spheres = *(obj.getSpheres());
}

/**
 * Assignment Operator
 * @param SimEntity - Simentity Object to copy from
 * @return Copied SimEntity object
 */
SimEntity& SimEntity::operator= (const SimEntity & rhs)
{
    name = rhs.getName();
    parent = rhs.getParent();
    this->physics = new SimPhysics(*(rhs.getPhysics()));
    advancedOption = *(rhs.getAdvancedOption());
    points = *(rhs.getPoints());
    triangles = *(rhs.getTriangles());
    rectangles = *(rhs.getRectangles());
    spheres = *(rhs.getSpheres());
    return *this;
}

SimEntity::~SimEntity()
{
    vector<AdvancedOption*>* av = &advancedOption;
    vector<AdvancedOption*>::iterator it;
    for(it = av->begin(); it != av->end(); it++)
    {
        delete (*it);
    }
    delete physics;
}

/**
 * @brief updates entity
 */
void SimEntity::update()
{
    physics->update();
}

/**
 * @brief sets parent entity. Used to calculate position of this entity
 * @param parent entity object ptr
 */
void SimEntity::setParent(SimEntity* parent)
{
    this->parent = parent;
}


/**
 * @brief Sets position of entity relative to parent(if exists)
 * @param x axis coord
 * @param y axis coord
 * @param z axis coord
 */
void SimEntity::setPosition(double x, double y, double z)
{
    physics->setPosition(x,y,z);
}



/**
 * @brief setPosition
 * @param p position to set
 */
void SimEntity::setPosition(Point3D p)
{
    physics->setPosition(p);
}


/**
 * @brief Sets rotation of entity
 * @param a roll
 * @param b pitch
 * @param c yaw
 */
void SimEntity::setRotation(double a, double b, double c)
{
    physics->setRotation(a,b,c);
}

/**
 * @brief setRotation
 * @param p position to set
 */
void SimEntity::setRotation(array<double,3> p)
{
    physics->setRotation(p);
}

/**
 * @brief Sets name of entity
 * @param new_name name of entity to set
 */
void SimEntity::setName(std::string new_name)
{
    name = new_name;
}

/**
 * @brief get absolute position
 * @return position using Forward kinematics
 */
const Point3D SimEntity::getAbsolutePosition() const
{
    if(parent)
    {
        return add(parent->getAbsolutePosition(),
                   rotate(getPosition(),parent->getRotation()));
    }
    else
    {
        return getPosition();
    }
}


//----------------------------------------------------------------------------//
//                            END CLASS DEFINITION                            //
//----------------------------------------------------------------------------//
