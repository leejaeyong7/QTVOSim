#include "simGround.h"

SimGround::SimGround(std::string _name,
                     int xCount, int yCount,
                     double width):
    SimEnvironment(_name,0,0,0,0,0,0,0)
{
    addOption("X Count",xCount);
    addOption("Y Count",yCount);
    addOption("Width",width);
    update();
}

void SimGround::update()
{
    SimEnvironment::update();
    getModel()->clear();
    int xCount= getOptionAsInt(0);
    int yCount= getOptionAsInt(1);
    double width = getOptionAsDouble(2);

    double maxX = (xCount/2)*width;
    double minX = -1*(xCount/2)*width;
    double maxY = (yCount/2)*width;
    double minY = -1*(yCount/2)*width;
    for(int i = 0; i < xCount; i++)
    {
        for(int j = 0; j < yCount; j++)
        {
            Line l1,l2;
            Point3D start1,start2;
            Point3D end1,end2;
            start1[0] = minX + i*width;
            start1[1] = minY;
            start1[2] = 0;
            end1[0] = minX + i*width;
            end1[1] = maxY;
            end1[2] = 0;

            start2[0] = minX;
            start2[1] = minY + j*width;
            start2[2] = 0;
            end2[0] = maxX;
            end2[1] = minY + j*width;
            end2[2] = 0;
            l1[0] = start1;
            l1[1] = end1;
            l2[0] = start2;
            l2[1] = end2;
            getModel()->addLine(l1);
            getModel()->addLine(l2);
        }
    }
}
