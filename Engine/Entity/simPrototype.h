#ifndef SIMPROTOTYPE_H
#define SIMPROTOTYPE_H
#include <array>
using namespace std;
//----------------------------------------------------------------------------//
//                            TYPEDEF DEFINITIONS                             //
//----------------------------------------------------------------------------//
template<class S, int X, int Y>
using Mat = array<array<S,Y>,X>;

template<class S, int X>
using SMat = Mat<S,X,X>;

template<int X>
using DSMat = SMat<double,X>;

typedef array<double,3> Point3D;
typedef array<double,2> Point2D;
typedef Mat<double,2,3> Line;
typedef Mat<double,3,3> Triangle;
typedef Mat<double,4,3> Rectangle;
typedef struct Sphere
{
    Point3D center;
    double radius;
}Sphere;


//----------------------------------------------------------------------------//
//                          END TYPEDEF DEFINITIONS                           //
//----------------------------------------------------------------------------//
#endif // SIMPROTOTYPE_H
