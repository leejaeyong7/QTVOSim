/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : simSensor.h
 * @brief      : Entity Sensor declaration file
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
#ifndef SIMSENSOR_H
#define SIMSENSOR_H
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include <vector>
#include "../simEntity.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                             CLASS DECLARATION                              //
//----------------------------------------------------------------------------//
class SimSensor : public SimEntity
{
public:
    /* default constructor */
    SimSensor(std::string _name,
              double x, double y, double z,
              double a, double b, double c,
              SimEntity *parent = 0);

    /* capture function that receives keypoints in scene */
    virtual vector<Point3D> capture() =0;
};
//----------------------------------------------------------------------------//
//                           END CLASS DECLARATION                            //
//----------------------------------------------------------------------------//
#endif // SIMSENSOR_H
