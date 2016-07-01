#ifndef _SIM_ENTITY_H_
#define _SIM_ENTITY_H_
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include <string>
#include <vector>
#include "Physics/simPhysics.h"
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

    // Getters
    /* Gets Parent entity ptr */
    SimEntity* getParent() const {return parent;}

    /* Gets physical property object */
    SimPhysics* getPhysics() const{return physics;}

    /* Gets position of entity relative to parent */
    const Point3D getPosition() const {return physics->getPosition();}

    /* Get relative position to parent */
    const Point3D getAbsolutePosition() const;

    /* Gets Rotation of entity */
    const array<double,3> getRotation() const {return physics->getRotation();}

    /* gets name of this entity */
    const std::string getName() const {return name;}

    /* gets advanced option pointer */
    const vector<AdvancedOption*>* getAdvancedOption() const {return &advancedOption;}

    /* gets Point vector pointer */
    const vector<Point3D>* getPoints() const {return &points;}

    /* gets Triangle vector pointer */
    const vector<Triangle>* getTriangles() const {return &triangles;}

    /* gets Rectangle vector pointer */
    const vector<Rectangle>* getRectangles() const {return &rectangles;}

    /* gets Spheres */
    const vector<Sphere>* getSpheres() const{return &spheres;}

    /* add Points */
    void addPoints(Point3D p);

    /* adds triangle to entity */
    void addTriangle(Triangle t);

    /* add Rectangles */
    void addRectangle(Rectangle r);

    /* add Spheres */
    void addSphere(Sphere s);

private:
    // parent entity
    SimEntity* parent;

    // physical property
    SimPhysics * physics;

    // name of entity
    std::string name;

    // Advanced options vector
    vector<AdvancedOption*> advancedOption;

    // Vector of Points for each entities
    vector<Point3D> points;

    // Vector of Triangles for each entity
    vector<Triangle> triangles;

    // Vector of Rectangles for each entity
    vector<Rectangle> rectangles;

    // vector of spheres for each entity
    vector<Sphere> spheres;

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
}; //END CLASS
#endif
