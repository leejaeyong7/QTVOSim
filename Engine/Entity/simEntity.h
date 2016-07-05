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
#include <iostream>
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
using namespace JAE_MATH_FUNCTIONS;
//----------------------------------------------------------------------------//
//                               END NAMESPACES                               //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                              CLASS DEFINITION                              //
//----------------------------------------------------------------------------//
class SimModel;
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
    virtual ~SimEntity();

    /* updates entity */
    virtual void update();

    /* draws entity */
    void draw(DSMat<4> ViewMatrix);

//----------------------------------------------------------------------------//
//                                  SETTERS                                   //
//----------------------------------------------------------------------------//
    /* sets parent entity (used for Forward Kinematics) */
    void setParent(SimEntity* parent);

    /* copies model drawing functions */
    void setModel(SimModel * proto);

    /* Sets position of entity relative to parent (if exists) */
    void setPosition(double x, double y, double z);

    /* Sets position of entity using array of 3 doubles */
    void setPosition(Point3D p);

    /* Sets rotation of entity */
    void setRotation(double a, double b, double c);

    /* setRotation */
    void setRotation(array<double,3> p);

    /* Sets name of entity */
    void setName(string new_name);

    /* adds option to advanced options */
    void setOption(int index, int option);
    void setOption(int index,double option);
    void setOption(int index,string option);

    void addOption(string label, int option);
    void addOption(string label, double option);
    void addOption(string label, string option);
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

    /* Gets Rotation of entity */
    const array<double,3> getRotation() const {return physics->getRotation();}

    /* gets transformation */
    DSMat<4> getTransformation();

    /* Get relative position to parent */
    DSMat<4> getAbsoluteTransformation();

    /* gets transformation */
    DSMat<4> getInverseTransformation();

    /* Gets translation matrix from position */
    DSMat<4> getTranslationMatrix();

    /* Gets Rotation matrix from position */
    DSMat<4> getRotationMatrix();

    /* gets name of this entity */
    const std::string getName() const {return name;}

    /* get advanced option vector */
    const vector<AdvancedOption*>* getAdvancedOption() const
        {
            return &advancedOption;
        }
    /* Gets option value at index */
    int getOptionAsInt(int index);
    double getOptionAsDouble(int index);
    string getOptionAsString(int index);

    /* gets label of advanced option */
    string getOptionLabel(int index);

    /* get length of advanced option */
    int getOptionLength();

    /* gets type of advanced option */
    OptionType getOptionType(int index);

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

    /* advanced option vector */
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
