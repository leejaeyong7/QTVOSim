/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : simRobot.h
 * @brief      : Robot entity declaration file
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
#ifndef _SIM_ROBOT_H_
#define _SIM_ROBOT_H_
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include <algorithm>
#include <vector>
#include "../simEntity.h"
#include "../Sensor/simSensor.h"
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                                 NAMESPACES                                 //
//----------------------------------------------------------------------------//
using namespace std;
//----------------------------------------------------------------------------//
//                               END NAMESPACES                               //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                             CLASS DECLARATION                              //
//----------------------------------------------------------------------------//
/* forward declaration */
class SimSensor;
class SimRobot: public SimEntity
{
public:
    /* default constructor */
    SimRobot(std::string _name,
             double x, double y, double z,
             double a, double b, double c, SimEntity* parent = 0);

    /* default destructor */
    ~SimRobot();

    virtual void update();

    /* adds sensor to robot */
    void addSensor(SimSensor* obj);

    /* removes sensor to robot */
    void removeSensor(SimSensor* obj);

    /**
     * Get sensor vector pointer attached to robot
     * @return vector<SimSensor*>* - pointer to vector
     */
    vector<SimSensor*>* getSensorVector(){return &sensorVector;}

private:
    vector<SimSensor*> sensorVector;
};
//----------------------------------------------------------------------------//
//                           END CLASS DECLARATION                            //
//----------------------------------------------------------------------------//
#endif
