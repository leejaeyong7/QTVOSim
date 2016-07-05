#include "simMath.h"
namespace JAE_MATH_FUNCTIONS{

double add(double a, double b)
{
    return a+b;
}
double minus(double a, double b)
{
    return a-b;
}

double multiply(double a, double b)
{
    return a*b;
}

double over(double a, double b)
{
    return (a>b) ? a : b-a;
}

double less(double a, double b)
{
    return (a < b) ? a : a - b;
}

double toDeg(double rad)
{
    return rad * 180.0 / PI;
}

double toRad(double deg)
{
    return deg * PI / 180.0;
}

double fitDeg(double deg)
{
    return less(over(deg,-360),360);
}

double fitRad(double rad)
{
    return less(over(rad,-2*PI),2*PI);
}
double length(Point3D p1, Point3D p2)
{
    array<double,3> sub = tensor<3>(minus,p1,p2);
    sub = tensor<3>(multiply,sub,sub);

    return sqrt(sub[0] + sub[1] + sub[2]);
}

array<double,3> cross(Point3D p1, Point3D p2)
{
    array<double,3> ret = {{0}};
    ret[0] = p1[1]*p2[2] - p1[2]*p2[1];
    ret[1] = p1[2]*p2[0] - p1[0]*p2[2];
    ret[2] = p1[0]*p2[1] - p1[1]*p2[0];
    return ret;
}

Mat<double,4,1> toHomogenous(Point3D p)
{
    Mat<double,4,1> ret;
    ret[0][0] = p[0];
    ret[1][0] = p[1];
    ret[2][0] = p[2];
    ret[3][0] = 1;
    return ret;
}
Point3D toPoint(Mat<double,4,1> p)
{
    Point3D ret;
    ret[0] = p[0][0];
    ret[1] = p[1][0];
    ret[2] = p[2][0];
    return ret;
}

DSMat<4> translationMatrix(array<double,3> trans)
{
    DSMat<4> ret = {{{0}}};
    ret[0][0] = 1;
    ret[1][1] = 1;
    ret[2][2] = 1;
    ret[3][3] = 1;
    ret[0][3] = trans[0];
    ret[1][3] = trans[1];
    ret[2][3] = trans[2];
    return ret;
}
DSMat<4> rotationMatrix(array<double,3> rot)
{
    DSMat<4> ret = {{0}};
    double a = toRad(rot[0]);
    double b = toRad(rot[1]);
    double c = toRad(rot[2]);

    ret[0][0] = cos(b)*cos(c);
    ret[0][1] = sin(a)*sin(b)*cos(c) - cos(a)*sin(c);
    ret[0][2] = cos(a)*sin(b)*cos(c) + sin(a)*sin(c);

    ret[1][0] = cos(b)*sin(c);
    ret[1][1] = sin(a)*sin(b)*sin(c) + cos(a)*cos(c);
    ret[1][2] = cos(a)*sin(b)*sin(c) - sin(a)*cos(c);

    ret[2][0] = -1*sin(b);
    ret[2][1] = sin(a)*cos(b);
    ret[2][2] = cos(a)*cos(b);

    ret[3][3] = 1;

    return ret;
}

array<double,3> rotationVector(DSMat<4> trans)
{
    array<double,3> ret = {{0}};
    ret[0] = atan2(trans[2][1],trans[2][2]);
    ret[1] = asin(-1*trans[2][0]);
    ret[2] = atan2(trans[1][0],trans[0][0]);
    return apply<3>(fitDeg,apply<3>(toDeg,ret));
}

Point3D positionVector(DSMat<4> trans)
{
    Point3D ret = {{0}};
    ret[0] = trans[0][3];
    ret[1] = trans[1][3];
    ret[2] = trans[2][3];
    return ret;
}
DSMat<4> inverse(DSMat<4> m)
{

    DSMat<4> ret;
    ret[0][0] = m[1][1]  * m[2][2] * m[3][3] -
                m[1][1]  * m[2][3] * m[3][2] -
                m[2][1] * m[1][2]  * m[3][3] +
                m[2][1] * m[1][3]  * m[3][2] +
                m[3][1] * m[1][2]  * m[2][3] -
                m[3][1] * m[1][3]  * m[3][3];

    ret[1][0] = -m[1][0]  * m[2][2] * m[3][3] +
              m[1][0]  * m[2][3] * m[3][2] +
              m[2][0]  * m[1][2]  * m[3][3] -
              m[2][0]  * m[1][3]  * m[3][2] -
              m[3][0]* m[1][2]  * m[2][3] +
              m[3][0]* m[1][3]  * m[3][3];

    ret[2][0] = m[1][0]  * m[2][1]* m[3][3] -
             m[1][0]  * m[2][3] * m[3][1] -
             m[2][0]  * m[1][1] * m[3][3] +
             m[2][0]  * m[1][3] * m[3][1] +
             m[3][0]* m[1][1] * m[2][3] -
             m[3][0]* m[1][3] * m[3][2];

    ret[3][0] = -m[1][0]  * m[2][1]* m[3][2] +
               m[1][0]  * m[2][2] * m[3][1] +
               m[2][0]  * m[1][1] * m[3][2] -
               m[2][0]  * m[1][2] * m[3][1] -
               m[3][0]* m[1][1] * m[2][2] +
               m[3][0]* m[1][2] * m[3][2];

    ret[0][1] = -m[0][1]  * m[2][2] * m[3][3] +
              m[0][1]  * m[2][3] * m[3][2] +
              m[2][1] * m[0][2] * m[3][3] -
              m[2][1] * m[0][3] * m[3][2] -
              m[3][1] * m[0][2] * m[2][3] +
              m[3][1] * m[0][3] * m[3][3];

    ret[1][1] = m[0][0]  * m[2][2] * m[3][3] -
             m[0][0]  * m[2][3] * m[3][2] -
             m[2][0]  * m[0][2] * m[3][3] +
             m[2][0]  * m[0][3] * m[3][2] +
             m[3][0]* m[0][2] * m[2][3] -
             m[3][0]* m[0][3] * m[3][3];

    ret[2][1] = -m[0][0]  * m[2][1]* m[3][3] +
              m[0][0]  * m[2][3] * m[3][1] +
              m[2][0]  * m[0][1] * m[3][3] -
              m[2][0]  * m[0][3] * m[3][1] -
              m[3][0]* m[0][1] * m[2][3] +
              m[3][0]* m[0][3] * m[3][2];

    ret[3][1] = m[0][0]  * m[2][1]* m[3][2] -
              m[0][0]  * m[2][2] * m[3][1] -
              m[2][0]  * m[0][1] * m[3][2] +
              m[2][0]  * m[0][2] * m[3][1] +
              m[3][0]* m[0][1] * m[2][2] -
              m[3][0]* m[0][2] * m[3][2];

    ret[0][2] = m[0][1]  * m[1][2] * m[3][3] -
             m[0][1]  * m[1][3] * m[3][2] -
             m[1][1]  * m[0][2] * m[3][3] +
             m[1][1]  * m[0][3] * m[3][2] +
             m[3][1] * m[0][2] * m[1][3] -
             m[3][1] * m[0][3] * m[2][3];

    ret[1][2] = -m[0][0]  * m[1][2] * m[3][3] +
              m[0][0]  * m[1][3] * m[3][2] +
              m[1][0]  * m[0][2] * m[3][3] -
              m[1][0]  * m[0][3] * m[3][2] -
              m[3][0]* m[0][2] * m[1][3] +
              m[3][0]* m[0][3] * m[2][3];

    ret[2][2] = m[0][0]  * m[1][1] * m[3][3] -
              m[0][0]  * m[1][3] * m[3][1] -
              m[1][0]  * m[0][1] * m[3][3] +
              m[1][0]  * m[0][3] * m[3][1] +
              m[3][0]* m[0][1] * m[1][3] -
              m[3][0]* m[0][3] * m[2][2];

    ret[3][2] = -m[0][0]  * m[1][1] * m[3][2] +
               m[0][0]  * m[1][2] * m[3][1] +
               m[1][0]  * m[0][1] * m[3][2] -
               m[1][0]  * m[0][2] * m[3][1] -
               m[3][0]* m[0][1] * m[1][2] +
               m[3][0]* m[0][2] * m[2][2];

    ret[0][3] = -m[0][1] * m[1][2] * m[2][3] +
              m[0][1] * m[1][3] * m[2][2] +
              m[1][1] * m[0][2] * m[2][3] -
              m[1][1] * m[0][3] * m[2][2] -
              m[2][1]* m[0][2] * m[1][3] +
              m[2][1]* m[0][3] * m[2][3];

    ret[1][3] = m[0][0] * m[1][2] * m[2][3] -
             m[0][0] * m[1][3] * m[2][2] -
             m[1][0] * m[0][2] * m[2][3] +
             m[1][0] * m[0][3] * m[2][2] +
             m[2][0] * m[0][2] * m[1][3] -
             m[2][0] * m[0][3] * m[2][3];

    ret[2][3] = -m[0][0] * m[1][1] * m[2][3] +
               m[0][0] * m[1][3] * m[2][1]+
               m[1][0] * m[0][1] * m[2][3] -
               m[1][0] * m[0][3] * m[2][1]-
               m[2][0] * m[0][1] * m[1][3] +
               m[2][0] * m[0][3] * m[2][2];

    ret[3][3] = m[0][0] * m[1][1] * m[2][2] -
              m[0][0] * m[1][2] * m[2][1]-
              m[1][0] * m[0][1] * m[2][2] +
              m[1][0] * m[0][2] * m[2][1]+
              m[2][0] * m[0][1] * m[1][2] -
              m[2][0] * m[0][2] * m[2][2];

    double det = m[0][0] * ret[0][0] + m[0][1] * ret[1][0]
            + m[0][2] * ret[2][0] + m[0][3] * ret[3][0];


    for (int i = 0; i < 4; i++)
    {
        for(int j = 0; j< 4; j++)
        {
            ret[i][j] = ret[i][j]/det;
        }
    }
    return ret;
}

}
