#ifndef SIMGROUND_H
#define SIMGROUND_H

#include "simenvironment.h"

class SimGround: public SimEnvironment
{
public:
    SimGround(std::string _name,
              int xCount, int yCount,
              double width);
    virtual void update();
};

#endif // SIMGROUND_H
