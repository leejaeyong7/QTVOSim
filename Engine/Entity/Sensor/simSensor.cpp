#include "simSensor.h"

SimSensor::SimSensor(std::string _name,
                     double x, double y, double z,
                     double a, double b, double c,
                     SimEntity * parent):
    SimEntity(_name,x,y,z,a,b,c,parent)
{

}
