/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : simEntity.h
 * @brief      : Entity declaration file
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
#ifndef _SIM_ENTITY_H_
#define _SIM_ENTITY_H_
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include <string>
#include <vector>
#include "Physics/simPhysics.h"
#include "Model/simModel.h"
#include "simEntityOption.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                                 NAMESPACES                                 //
//----------------------------------------------------------------------------//
using namespace std;
//----------------------------------------------------------------------------//
//                               END NAMESPACES                               //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                              CLASS DEFINITION                              //
//----------------------------------------------------------------------------//
class SimEntity
{
//----------------------------------------------------------------------------//
//                        PUBLIC FUNCTION DECLARATIONS                        //
//----------------------------------------------------------------------------//
public:
    /* default constructor */
    SimEntity(std::string _name,
              double x, double y, double z,
              double a, double b, double c,
              SimEntity * parent = 0);

    /* copy constructor */
    SimEntity(const SimEntity & obj);

    /* assignment operator */
    SimEntity& operator= (const SimEntity & rhs);

    /* default desructor */
    ~SimEntity();

    /* updates entity */
    void update();

//----------------------------------------------------------------------------//
//                                  SETTERS                                   //
//----------------------------------------------------------------------------//
    /* sets parent entity (used for Forward Kinematics) */
    void setParent(SimEntity* parent);

    /* Sets position of entity relative to parent (if exists) */
    void setPosition(double x, double y, double z);

    /* Sets position of entity using array of 3 doubles */
    void setPosition(Point3D p);

    /* Sets rotation of entity */
    void setRotation(double a, double b, double c);

    /* setRotation */
    void setRotation(array<double,3> p);

    /* Sets name of entity */
    void setName(std::string new_name);
//----------------------------------------------------------------------------//
//                                  GETTERS                                   //
//----------------------------------------------------------------------------//
    /* Gets Parent entity ptr */
    SimEntity* getParent() const {return parent;}

    /* Gets physical property object */
    SimPhysics* getPhysics() const{return physics;}

    /* Get model of entity */
    SimModel* getModel() const{return model;}

    /* Gets position of entity relative to parent */
    const Point3D getPosition() const {return physics->getPosition();}

    /* Get relative position to parent */
    const Point3D getAbsolutePosition() const;

    /* Gets Rotation of entity */
    const array<double,3> getRotation() const {return physics->getRotation();}

    /* gets name of this entity */
    const std::string getName() const {return name;}

    /* gets advanced option pointer */
    const vector<AdvancedOption*>* getAdvancedOption() const
        {
            return &advancedOption;
        }


//----------------------------------------------------------------------------//
//                      END PUBLIC FUNCTION DECLARATIONS                      //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                          CLASS PRIVATE VARIABLES                           //
//----------------------------------------------------------------------------//
private:
    // parent entity
    SimEntity* parent;

    // physical property
    SimPhysics * physics;

    // simulator model
    SimModel * model;

    // name of entity
    std::string name;

    // Advanced options vector
    vector<AdvancedOption*> advancedOption;

    // check advanced option label
    struct checkLabel
    {
        checkLabel(std::string label) : str_holder(label) {}
        std::string str_holder;
        bool operator()(AdvancedOption* obj)
        {
            return obj->label == str_holder;
        }
    };
//----------------------------------------------------------------------------//
//                        END CLASS PRIVATE VARIABLES                         //
//----------------------------------------------------------------------------//
}; //END CLASS
//----------------------------------------------------------------------------//
//                           END CLASS DECLARATION                            //
//----------------------------------------------------------------------------//
#endif
