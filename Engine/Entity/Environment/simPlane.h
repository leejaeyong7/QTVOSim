#ifndef SIMPLANE_H
#define SIMPLANE_H

#include "simenvironment.h"

class SimPlane : public SimEnvironment
{
public:
    SimPlane(string _name,
             double x, double y, double z,
             double a, double b, double c,
             double width, double height,
             SimEntity* parent = 0);
    virtual void update();
};

#endif // SIMPLANE_H
