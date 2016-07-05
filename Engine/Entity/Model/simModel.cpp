/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : simModel.cpp
 * @brief      : Entity Model definition file
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include "simModel.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                              CLASS DEFINITION                              //
//----------------------------------------------------------------------------//

/**
 * @brief default constructor
 */
SimModel::SimModel()
{
    pointDrawFunc = 0;
    lineDrawFunc = 0;
    triangleDrawFunc = 0;
    rectangleDrawFunc = 0;
    sphereDrawFunc = 0;
}
/**
 * @brief copy constructor
 * @param obj sim model object to copy
 */
SimModel::SimModel(const SimModel & obj)
{
    points = obj.points;
    lines = obj.lines;
    triangles = obj.triangles;
    rectangles = obj.rectangles;
    spheres = obj.spheres;
    pointDrawFunc = obj.pointDrawFunc;
    lineDrawFunc = obj.lineDrawFunc;
    triangleDrawFunc = obj.triangleDrawFunc;
    rectangleDrawFunc = obj.rectangleDrawFunc;
    sphereDrawFunc = obj.sphereDrawFunc;
}

/**
 * @brief assignment operator
 * @param rhs sim model object to copy
 */
SimModel & SimModel::operator=(const SimModel & rhs)
{
    points = rhs.points;
    lines = rhs.lines;
    triangles = rhs.triangles;
    rectangles = rhs.rectangles;
    spheres = rhs.spheres;
    pointDrawFunc = rhs.pointDrawFunc;
    lineDrawFunc = rhs.lineDrawFunc;
    triangleDrawFunc = rhs.triangleDrawFunc;
    rectangleDrawFunc = rhs.rectangleDrawFunc;
    sphereDrawFunc = rhs.sphereDrawFunc;
    return *this;
}

/**
 * @brief destructor
 */
SimModel::~SimModel()
{

}


/**
 * @brief add Points
 * @param p array of 3 doubles
 */
void SimModel::addPoint(Point3D p)
{
    points.push_back(p);
}


/**
 * @brief add Spheres
 * @param s Sphere struct
 */
void SimModel::addLine(Line l)
{
    lines.push_back(l);
}


/**
 * @brief adds triangle to entity
 * @param t array of 3 arrays of 3 doubles
 */
void SimModel::addTriangle(Triangle t)
{
    triangles.push_back(t);
}

/**
 * @brief add Rectangles
 * @param r array of 4 arrays of 3 doubles
 */
void SimModel::addRectangle(Rectangle r)
{
    rectangles.push_back(r);
}

/**
 * @brief add Spheres
 * @param s Sphere struct
 */
void SimModel::addSphere(Sphere s)
{
    spheres.push_back(s);
}


/**
 * @brief draw all forms
 */
void SimModel::draw(DSMat<4> ModelMat)
{
    drawPoint(ModelMat);
    drawLine(ModelMat);
    drawTriangle(ModelMat);
    drawRectangle(ModelMat);
    drawSphere(ModelMat);
}


/**
 * @brief sets point drawing function ptr
 * @param func
 */
void SimModel::setPointDraw(pointDraw func)
{
    pointDrawFunc = func;
}

/**
 * @brief sets line drawing function ptr
 * @param func
 */
void SimModel::setLineDraw(lineDraw func)
{
    lineDrawFunc = func;
}

/**
 * @brief sets triangle drawing function ptr
 * @param func
 */
void SimModel::setTriangleDraw(triangleDraw func)
{
    triangleDrawFunc = func;
}

/**
 * @brief sets rect drawing function ptr
 * @param func
 */
void SimModel::setRectangleDraw(rectangleDraw func)
{
    rectangleDrawFunc = func;
}

/**
 * @brief sets Sphere drawing function ptr
 * @param func
 */
void SimModel::setSphereDraw(sphereDraw func)
{
    sphereDrawFunc = func;
}

/**
 * @brief clears all
 */
void SimModel::clear()
{
    clearPoints();
    clearLines();
    clearRectangles();
    clearTriangles();
    clearSpheres();
}

/**
 * @brief clears point vector
 */
void SimModel::clearPoints()
{
    points.clear();
}
/**
 * @brief clears line vector
 */
void SimModel::clearLines()
{
    lines.clear();
}
/**
 * @brief clears triangle vector
 */
void SimModel::clearTriangles()
{
    triangles.clear();
}
/**
 * @brief clears rect vector
 */
void SimModel::clearRectangles()
{
    rectangles.clear();
}
/**
 * @brief clears sphere vector
 */
void SimModel::clearSpheres()
{
    spheres.clear();
}
/**
 * @brief draws point
 */
void SimModel::drawPoint(DSMat<4> Transformation)
{
    if(pointDrawFunc)
    {
        vector<Point3D>::iterator it;
        for(it = points.begin();
            it != points.end();
            it++)
        {
            Point3D p = toPoint(
                        multiply<double,4,4,1>(Transformation,
                                               toHomogenous(*it)));

            pointDrawFunc(p);
        }
    }
}
/**
 * @brief draws lines
 */
void SimModel::drawLine(DSMat<4> Transformation)
{
    if(lineDrawFunc)
    {
        vector<Line>::iterator it;
        for(it = lines.begin();
            it != lines.end();
            it++)
        {
           Line l;
           for(int i = 0; i < 2; i++)
           {
                l[i] = toPoint(
                        multiply<double,4,4,1>(Transformation,
                                               toHomogenous((*it)[i])));
           }
           lineDrawFunc(l);
        }
    }
}
/**
 * @brief draw triangle
 */
void SimModel::drawTriangle(DSMat<4> Transformation)
{
    
    if(triangleDrawFunc)
    {
        vector<Triangle>::iterator it;
        for(it = triangles.begin();
            it != triangles.end();
            it++)
        {
           Triangle t;
           for(int i = 0; i < 3; i++)
           {
                t[i] = toPoint(
                        multiply<double,4,4,1>(Transformation,
                                               toHomogenous((*it)[i])));
           }
            triangleDrawFunc(t);
        }
    }
}
/**
 * @brief draw rectangle
 */
void SimModel::drawRectangle(DSMat<4> Transformation)
{
    
    if(rectangleDrawFunc)
    {
        vector<Rectangle>::iterator it;
        for(it = rectangles.begin();
            it != rectangles.end();
            it++)
        {
            Rectangle r;
            for(int i = 0; i < 4; i++)
            {
                r[i] = toPoint(
                        multiply<double,4,4,1>(Transformation,
                                               toHomogenous((*it)[i])));
            }
            rectangleDrawFunc(r);
        }
    }
}
/**
 * @brief draw sphere
 */
void SimModel::drawSphere(DSMat<4> Transformation)
{
    
    if(sphereDrawFunc)
    {
        vector<Sphere>::iterator it;
        for(it = spheres.begin();
            it != spheres.end();
            it++)
        {
            Sphere s;
            s.center = toPoint(
                        multiply<double,4,4,1>(Transformation,
                                               toHomogenous((*it).center)));
            s.radius = (*it).radius;
            sphereDrawFunc(s);
        }
    }
}
//----------------------------------------------------------------------------//
//                            END CLASS DEFINITION                            //
//----------------------------------------------------------------------------//

