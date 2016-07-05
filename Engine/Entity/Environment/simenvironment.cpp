#include "simenvironment.h"

SimEnvironment::SimEnvironment(std::string _name,
                               double x, double y, double z,
                               double a, double b, double c,
                               SimEntity * parent):
    SimEntity(_name,x,y,z,a,b,c,parent)
{
    update();
}

void SimEnvironment::addKeyPoint(Rectangle r, int num)
{
    if(num)
    {
        Point3D top_left = r[0];
        Point3D top_right= r[1];
        Point3D bot_right= r[2];
        Point3D bot_left=  r[3];

        array<double,3> u = tensor<3>(JAE_MATH_FUNCTIONS::minus,
                                      top_right,top_left);
        array<double,3> v = tensor<3>(JAE_MATH_FUNCTIONS::minus,
                                      bot_right,top_left);

        Point3D normal = cross(u,v);

        int imin = 0;
        for(int i=0; i<3; ++i)
            if(abs(normal[i]) < abs(normal[imin]))
                imin = i;

        Point3D v2 = {{0}};
        double dt    = normal[imin];

        v2[imin] = 1;
        for(int i=0;i<3;i++)
            v2[i] -= dt*normal[i];
        Point3D v3 = cross(v2,normal);
        DSMat<4> trans = {{{0}}};
        for(int i = 0; i<3;i++)
        {
            trans[0][i] = v2[i];
            trans[1][i] = v3[i];
            trans[2][i] = normal[i];
        }
        trans[3][3] = 1;


        int sn = round(sqrt(num));
        int ho = (num % sn == 0) ? 0 : 1;
        double w = length(top_left,top_right);
        double h = length(top_left,bot_left);

        for(int i = 0; i < num ; i++)
        {
            Point3D k;
            k[0] = ((i % sn)+0.5 - ((double)sn/2))*w/sn;
            k[1] = ((i / sn)+0.5 -((double)((num/sn)+ho)/2))*
                    h/((double)(num/sn)+ho);
            k[2] = 0;
            getModel()->addPoint(k);
        }
    }
}

void SimEnvironment::update()
{
    SimEntity::update();
}
