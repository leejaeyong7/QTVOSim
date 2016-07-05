#ifndef SIMENVIRONMENT_H
#define SIMENVIRONMENT_H

#include "../simEntity.h"
class SimEnvironment: public SimEntity
{
public:
    /* default constructor */
    SimEnvironment(std::string _name,
                   double x, double y, double z,
                   double a, double b, double c,
                   SimEntity * parent = 0);

    virtual void update();

    void addKeyPoint(Rectangle r, int num);
    vector <Point3D>* getKeyPoints(){return &keyPoints;}
private:
    vector <Point3D> keyPoints;
};

#endif // SIMENVIRONMENT_H
