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
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                             CLASS DECLARATION                              //
//----------------------------------------------------------------------------//
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
    void addLIne(Line l);

    /* adds triangle to entity */
    void addTriangle(Triangle t);

    /* add Rectangles */
    void addRectangle(Rectangle r);

    /* add Spheres */
    void addSphere(Sphere s);

    /* draw all forms */
    void draw();

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
    void drawPoint();

    /* draws a line */
    void drawLine();

    /* draws a triangle */
    void drawTriangle();

    /* draws rectangle */
    void drawRectangle();
    
    /* draws a sphere */
    void drawSphere();

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
