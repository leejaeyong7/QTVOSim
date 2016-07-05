#ifndef SIMMATH_H
#define SIMMATH_H

#include <array>
#include <vector>
#include <cmath>
#include "../simPrototype.h"
using namespace std;
#define PI 3.1415926535
//----------------------------------------------------------------------------//
//                        HELPER FUNCTION DEFINITIONS                         //
//----------------------------------------------------------------------------//
namespace JAE_MATH_FUNCTIONS{
//----------------------------------------------------------------------------//
//                            TYPEDEF DEFINITIONS                             //
//----------------------------------------------------------------------------//
typedef double (*fun_1)(double a);
typedef double (*fun_2)(double a,double b);
//----------------------------------------------------------------------------//
//                          END TYPEDEF DEFINITIONS                           //
//----------------------------------------------------------------------------//
extern double add(double a, double b);
extern double minus(double a, double b);
extern double multiply(double a, double b);
extern double over(double a, double b);
extern double less(double a, double b);
extern double toDeg(double rad);
extern double toRad(double deg);
extern double fitDeg(double deg);
extern double fitRad(double rad);
extern Mat<double,4,1> toHomogenous(Point3D p);
extern Point3D toPoint(Mat<double,4,1> p);

extern DSMat<4> translationMatrix(array<double,3> trans);
extern DSMat<4> rotationMatrix(array<double,3> rot);
extern Point3D positionVector(DSMat<4>trans);
extern array<double,3> rotationVector(DSMat<4>trans);

/**
 * @brief SimPhysics::map
 * @param orig original point
 * @param param parameter to be used
 * @param func funtion to apply that takes two variables
 * @return array with map operation of func
 */
template<int T>
extern array<double,T> map(fun_2 func,array<double,T> orig, double param)
{
    array<double,T> ret;
    for(int i = 0;  i < T; i++)
    {
        ret[i] = func(orig[i],param);
    }
    return ret;
}
/**
 * @brief SimPhysics::apply
 * @param p1 point1
 * @param func function that takes one variables
 * @return array with func applied to each element
 */
template<int T>
extern array<double,T> apply(fun_1 func,array<double,T> orig)
{
    array<double,T> ret;
    for(int i = 0; i < T; i++)
    {
        ret[i] = func(orig[i]);
    }
    return ret;
}

/**
 * @brief tensor operation for array of same length
 * @param p1 point1
 * @param p2 point 2
 * @param func function that takes two variables
 * @return array with tensor operation of func
 */
template<int T>
extern array<double,T> tensor(fun_2 func,
                              array<double,T> p1,
                              array<double,T> p2)
{
    array<double,T> ret;
    for(int i = 0; i < T; i++)
    {
        ret[i] = func(p1[i],p2[i]);
    }
    return ret;
}

// matrix operations
template<class S, int X, int Y>
extern Mat<S,X,Y> add(Mat<S,X,Y> m1, Mat<S,X,Y> m2)
{
    Mat<S,X,Y> ret;
    for(int i = 0; i < X; i++)
    {
        for(int j= 0;  j<Y; j++)
        {
            ret[i][j] = m1[i][j]+m2[i][j];
        }
    }
    return ret;
}

template<class S, int X,int T,int Y>
extern Mat<S,X,Y> multiply(Mat<S,X,T> m1, Mat<S,T,Y> m2)
{
    Mat<S,X,Y> ret = {{{0}}};
    for(int i = 0; i < X; i++)
    {
        for(int j = 0; j< Y; j++)
        {
            for(int t = 0; t<T; t++)
            {
                ret[i][j] += m1[i][t]*m2[t][j];
            }
        }
    }
    return ret;
}

template<int X>
extern DSMat<X> multiply(DSMat<X>m1, DSMat<X> m2)
{
    return multiply<double,X,X,X>(m1,m2);
}

template<int X>
extern DSMat<X> apply(fun_1 func, DSMat<X>orig)
{
    DSMat<X> ret;
    for(int i = 0; i < X; i++)
    {
        ret[i] = apply<X>(func,orig[i]);
    }
    return ret;
}

template<int X>
extern DSMat<X> tensor(fun_1 func, DSMat<X>m1, DSMat<X>m2)
{
    DSMat<X> ret;
    for(int i = 0; i < X; i++)
    {
        ret[i] = tensor<X>(func,m1[i],m2[i]);
    }
    return ret;
}

template<int X>
extern DSMat<X> map(fun_1 func, DSMat<X>m1, double param)
{
    DSMat<X> ret;
    for(int i = 0; i < X; i++)
    {
        ret[i] = map<X>(func,m1[i],param);
    }
    return ret;
}

template<int X>
extern DSMat<X> transpose(DSMat<X> m)
{
    DSMat<X> ret = {{{0}}};
    for(int i = 0; i < X; i++)
    {
        for(int j =0; j < X; j++)
        {
            ret[i][j] = m[j][i];
        }
    }
    return ret;
}
extern DSMat<4> inverse(DSMat<4> m);

template<int X>
extern Mat<double,X,1> normalize(Mat<double,X,1> m)
{
    Mat<double,X,1> ret;
    double sum = 0;
    for(int i = 0; i<4; i++)
    {
        sum += m[i][0]*m[i][0];
    }
    for(int i = 0; i<4; i++)
    {
        ret[i][0] = m[i][0]/sqrt(sum);
    }
    return ret;
}
extern double length(Point3D p1, Point3D p2);
extern array<double,3> cross(Point3D p1, Point3D p2);


}
//----------------------------------------------------------------------------//
//                      END HELPER FUNCTION DEFINITIONS                       //
//----------------------------------------------------------------------------//
#endif // SIMMATH_H
