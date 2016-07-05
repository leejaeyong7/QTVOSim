#include "simPlane.h"

SimPlane::SimPlane(string _name,
                   double x, double y, double z,
                   double a, double b, double c,
                   double width, double height,
                   SimEntity * parent)
    :SimEnvironment(_name,x,y,z,a,b,c,parent)
{
    addOption("Width",width);
    addOption("Height",height);
    addOption("KeyPoints",(int)0);
    update();
}
void SimPlane::update()
{
    double width = getOptionAsDouble(0);
    double height = getOptionAsDouble(1);
    int num_f = getOptionAsInt(2);
    SimEnvironment::update();
    getModel()->clear();
    Rectangle r;
    Point3D ul = {{-1*width,height,0}};
    Point3D ur = {{width,height,0}};
    Point3D dr = {{width,-1*height,0}};
    Point3D dl = {{-1*width,-1*height,0}};
    r[0] = ul;
    r[1] = ur;
    r[2] = dr;
    r[3] = dl;
    //cout<<num_f<<endl;
    addKeyPoint(r,num_f);
    getModel()->addRectangle(r);
}
