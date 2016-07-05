/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : simModel.h
 * @brief      : Entity Model file
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
#ifndef SIMMODEL_H
#define SIMMODEL_H
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include <vector>
#include "../simEntity.h"
#include "../simPrototype.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                            TYPEDEF DEFINITIONS                             //
//----------------------------------------------------------------------------//
typedef void (*pointDraw)(Point3D);
typedef void (*lineDraw)(Line);
typedef void (*triangleDraw)(Triangle);
typedef void (*rectangleDraw)(Rectangle);
typedef void (*sphereDraw)(Sphere);
//----------------------------------------------------------------------------//
//                          END TYPEDEF DEFINITIONS                           //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                             CLASS DECLARATION                              //
//----------------------------------------------------------------------------//
class SimEntity;
class SimModel
{
public:
    /* default constructor */
    SimModel();

    /* copy constructor */
    SimModel(const SimModel & obj);

    /* assignment operator */
    SimModel & operator=(const SimModel & rhs);

    /* destructor */
    ~SimModel();

    /* gets Point vector pointer */
    const vector<Point3D>* getPoints() const {return &points;}

    /* gets line vector pointer */
    const vector<Line>* getLines() const {return &lines;}

    /* gets Triangle vector pointer */
    const vector<Triangle>* getTriangles() const {return &triangles;}

    /* gets Rectangle vector pointer */
    const vector<Rectangle>* getRectangles() const {return &rectangles;}

    /* gets Spheres */
    const vector<Sphere>* getSpheres() const{return &spheres;}

    /* add Points */
    void addPoint(Point3D p);

    /* add lines */
    void addLine(Line l);

    /* adds triangle to entity */
    void addTriangle(Triangle t);

    /* add Rectangles */
    void addRectangle(Rectangle r);

    /* add Spheres */
    void addSphere(Sphere s);

    /* draw all forms */
    void draw(DSMat<4> ModelMatrix);

    /* sets function that draws point */
    void setPointDraw(pointDraw func);

    /* sets function that draws line */
    void setLineDraw(lineDraw func);

    /* sets function that draws triangle */
    void setTriangleDraw(triangleDraw func);

    /* sets function that draws rectangle */
    void setRectangleDraw(rectangleDraw func);

    /* sets function that draws sphere */
    void setSphereDraw(sphereDraw func);

    /* gets function that draws point */
    pointDraw getPointDraw(){return pointDrawFunc;}

    /* gets function that draws line */
    lineDraw getLineDraw(){return lineDrawFunc;}

    /* gets function that draws triangle */
    triangleDraw getTriangleDraw(){return triangleDrawFunc;}

    /* gets function that draws rectangle */
    rectangleDraw getRectangleDraw(){return rectangleDrawFunc;}

    /* gets function that draws sphere */
    sphereDraw getSphereDraw(){return sphereDrawFunc;}

    /* clears all */
    void clear();
private:
    /* clears point vector */
    void clearPoints();

    /* clears line vector */
    void clearLines();

    /* clears triangle vector */
    void clearTriangles();

    /* clears rectangle vector */
    void clearRectangles();

    /* clears sphere vector */
    void clearSpheres();

    /* draws a point */
    void drawPoint(DSMat<4> Transformation);

    /* draws a line */
    void drawLine(DSMat<4> Transformation);

    /* draws a triangle */
    void drawTriangle(DSMat<4> Transformation);

    /* draws rectangle */
    void drawRectangle(DSMat<4> Transformation);
    
    /* draws a sphere */
    void drawSphere(DSMat<4> Transformation);

    /* function that takes point to draw point */
    pointDraw pointDrawFunc;

    /* function that takes line to draw line */
    lineDraw lineDrawFunc;

    /* function that takes triangle to draw triangle */
    triangleDraw triangleDrawFunc;

    /* function that takes rectangle to draw rectangle */
    rectangleDraw rectangleDrawFunc;

    /* function that takes sphere to draw sphere */
    sphereDraw sphereDrawFunc;

    // Vector of Points for each entities
    vector<Point3D> points;

    // Vector of lines for each entities
    vector<Line> lines;

    // Vector of Triangles for each entity
    vector<Triangle> triangles;

    // Vector of Rectangles for each entity
    vector<Rectangle> rectangles;

    // vector of spheres for each entity
    vector<Sphere> spheres;
};
//----------------------------------------------------------------------------//
//                           END CLASS DECLARATION                            //
//----------------------------------------------------------------------------//
#endif // SIMMODEL_H
