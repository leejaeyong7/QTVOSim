#ifndef SIMSENSOR_H
#define SIMSENSOR_H
#include "../simEntity.h"
class SimSensor : public SimEntity
{
public:
    SimSensor(std::string _name,
              double x, double y, double z,
              double a, double b, double c,
              SimEntity *parent = 0);
};

#endif // SIMSENSOR_H
