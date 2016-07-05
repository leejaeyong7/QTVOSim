#ifndef SIMCAMERA_H
#define SIMCAMERA_H

//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include <vector>
#include "simSensor.h"
#include "../simPrototype.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//

class SimCamera : public SimSensor
{
public:
    /* default constructor */
    SimCamera(std::string _name,
              double x, double y, double z,
              double a, double b, double c,
              double fovx, double fovy, double fl,
              SimEntity *parent = 0);

    /* captures viewable scene */
    vector<Point3D> capture();

    DSMat<4> projectionMatrix();
    double getFovy();
    double getFovx();
    double getFl();
    double getZNear(){return zNear;}
    double getZFar(){return zFar;}
private:
    double zNear;
    double zFar;
};

#endif // SIMCAMERA_H
