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

}
/**
 * @brief copy constructor
 * @param obj sim model object to copy
 */
SimModel::SimModel(const SimModel & obj)
{

}

/**
 * @brief assignment operator
 * @param rhs sim model object to copy
 */
SimModel & SimModel::operator=(const SimModel & rhs)
{

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
void SimModel::addPoints(Point3D p)
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
void SimModel::draw()
{

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
void SimModel::drawPoint()
{
    
}
/**
 * @brief draws lines
 */
void SimModel::drawLine()
{
    
}
/**
 * @brief draw triangle
 */
void SimModel::drawTriangle()
{
    
}
/**
 * @brief draw rectangle
 */
void SimModel::drawRectangle()
{
    
}
/**
 * @brief draw sphere
 */
void SimModel::drawSphere()
{
    
}
//----------------------------------------------------------------------------//
//                            END CLASS DEFINITION                            //
//----------------------------------------------------------------------------//

