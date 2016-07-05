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
    model = new SimModel();
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
    model = new SimModel(*(obj.getModel()));
    advancedOption = *(obj.getAdvancedOption());
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
    physics = new SimPhysics(*(rhs.getPhysics()));
    model = new SimModel(*(rhs.getModel()));
    advancedOption = *(rhs.getAdvancedOption());
    return *this;
}

SimEntity::~SimEntity()
{
    vector<AdvancedOption*>* av = &advancedOption;
    vector<AdvancedOption*>::iterator it;
    for ( it = av->begin(); it != av->end(); )
    {
          delete (* it);
          it = av->erase(it);
    }
    delete physics;
    delete model;
}

/**
 * @brief updates entity
 */
void SimEntity::update()
{
    physics->update();
}

/**
 * @brief draws entity on scene
 */
void SimEntity::draw(DSMat<4> ViewMatrix)
{
    DSMat<4> ModelMat = multiply<4>(ViewMatrix,getAbsoluteTransformation());
    model->draw(ModelMat);
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
 * @brief copies model from given ptr
 * @param proto
 */
void SimEntity::setModel(SimModel *proto)
{
    *model = *proto;
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
 * @brief sets option for integer
 * @param index
 * @param option
 */
void SimEntity::setOption(int index, int option)
{
    ((AdvancedOption_Int*)(advancedOption[index]))->value = option;
}
/**
 * @brief sets option for double given index
 * @param index
 * @param option
 */
void SimEntity::setOption(int index, double option)
{
    ((AdvancedOption_Double*)(advancedOption[index]))->value = option;
}
/**
 * @brief sets option for string given index
 * @param index
 * @param option
 */
void SimEntity::setOption(int index, string option)
{
    ((AdvancedOption_String*)(advancedOption[index]))->value = option;
}

/**
 * @brief adds option type int to advanced options
 * @param label label of option
 * @param option value of option
 */
void SimEntity::addOption(string label, int option)
{
    AdvancedOption_Int * opt = new AdvancedOption_Int(label,option);
    advancedOption.push_back(opt);
}

/**
 * @brief adds option type double to advanced options
 * @param label label of option
 * @param option value of option
 */
void SimEntity::addOption(string label, double option)
{
    AdvancedOption_Double * opt = new AdvancedOption_Double(label,option);
    advancedOption.push_back(opt);
}

/**
 * @brief adds option type string to advanced options
 * @param label label of option
 * @param option value of option
 */
void SimEntity::addOption(string label, string option)
{
    AdvancedOption_String * opt = new AdvancedOption_String(label,option);
    advancedOption.push_back(opt);
}


/**
 * @brief get advanced Option value at index as integer
 * @param index
 */
int SimEntity::getOptionAsInt(int index)
{
    return ((AdvancedOption_Int*)(advancedOption[index]))->value;
/**
 * @brief get advanced Option value at index as double
 * @param index
 */
}
double SimEntity::getOptionAsDouble(int index)
{
    return ((AdvancedOption_Double*)(advancedOption[index]))->value;
}
/**
 * @brief get advanced Option value at index as String
 * @param index
 */
string SimEntity::getOptionAsString(int index)
{
    return ((AdvancedOption_String*)(advancedOption[index]))->value;
}
/**
 * @brief gets label of advanced option
 * @param index
 */
string SimEntity::getOptionLabel(int index)
{
    return advancedOption[index]->label;
}

/**
 * @brief get length of advanced option
 * @return
 */
int SimEntity::getOptionLength()
{
    return advancedOption.size();
}
/**
 * @brief gets type of advanced option
 * @param index
 */
OptionType SimEntity::getOptionType(int index)
{
    return advancedOption[index]->type;
}

/**
 * @brief get absolute position
 * @return position using Forward kinematics
 */
DSMat<4> SimEntity::getAbsoluteTransformation()
{
    if(parent)
    {
        return multiply<4>(parent->getAbsoluteTransformation(),
                           getAbsoluteTransformation());
    }
    else
    {
        return getTransformation();
    }
}

/**
 * @brief get translation matrix from position
 * @return translation matrix
 */
DSMat<4> SimEntity::getTranslationMatrix()
{
    return translationMatrix(getPosition());
}


/**
 * @brief gets rotation matrix from rotations
 * @return rotation matrix
 */
DSMat<4> SimEntity::getRotationMatrix()
{
    return rotationMatrix(getRotation());
}

/**
 * @brief gets transformation from this entity
 * @return 4x4 matrix
 */
DSMat<4> SimEntity::getTransformation()
{
    return multiply<4>(getTranslationMatrix(),getRotationMatrix());
}

/**
 * @brief gets transformation from this entity
 * @return 4x4 matrix
 */
DSMat<4> SimEntity::getInverseTransformation()
{
    DSMat<4> ret = {{{0}}};
    DSMat<4> rotMat = transpose<4>(rotationMatrix(getRotation()));
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            ret[i][j] = rotMat[i][j];
        }
    }
    Mat<double,4,1> posVec = {{{0}}};
    Point3D pos = getPosition();
    posVec[0][0] = -1*pos[0];
    posVec[1][0] = -1*pos[1];
    posVec[2][0] = -1*pos[2];
    posVec[3][0] = -1;
    posVec = multiply<double,4,4,1>(rotMat,posVec);
    for(int i = 0; i < 3; i++)
    {
        ret[i][3] = posVec[i][0];
    }

    ret[3][3] = 1;

    return ret;
}

//----------------------------------------------------------------------------//
//                            END CLASS DEFINITION                            //
//----------------------------------------------------------------------------//
