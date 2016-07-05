#include "simCamera.h"

SimCamera::SimCamera(std::string _name,
                     double x, double y, double z,
                     double a, double b, double c,
                     double fovx, double fovy, double fl,
                     SimEntity *parent):
        SimSensor(_name,x,y,z,a,b,c,parent)
{
    addOption("FOV X",fovx);
    addOption("FOV Y",fovy);
    addOption("Focal Length",fl);
    zNear = 0.0001;
    zFar = 99999;
}


DSMat<4> SimCamera::projectionMatrix()
{
    DSMat<4> ret = {{0}};
    double fovy = toRad(getFovy());
    double aspect = toRad(getFovx())/fovy;
    ret[0][0] = 1.0  / (aspect* tan(fovy/2));
    ret[1][1] = 1.0 / (tan(fovy/2));
    ret[2][2] = zFar / (zFar - zNear);
    ret[2][3] = 1;
    ret[3][2] = -1*(zFar*zNear)/(zFar - zNear);

    return ret;
}


double SimCamera::getFovy()
{
    return getOptionAsDouble(0);
}
double SimCamera::getFovx()
{
    return getOptionAsDouble(1);
}
double SimCamera::getFl()
{
    return getOptionAsDouble(2);
}


vector<Point3D> SimCamera::capture()
{
    vector<Point3D> ret;
    return ret;
}
