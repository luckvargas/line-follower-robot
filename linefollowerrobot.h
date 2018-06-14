#ifndef LINEFOLLOWERROBOT_H
#define LINEFOLLOWERROBOT_H

#include "linesensor.h"
#include "motorcontroller.h"

class LineSensor;
class MotorController;

class LineFollowerRobot {
public:
    LineFollowerRobot();

private:
    MotorController m_motorController;
    LineSensor m_lineSensor;
};

#endif // LINEFOLLOWERROBOT_H
