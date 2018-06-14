#ifndef LINEFOLLOWERROBOT_H
#define LINEFOLLOWERROBOT_H

#include "linesensor.h"
#include "motorcontroller.h"
#include <Arduino.h>

class LineSensor;
class MotorController;

class LineFollowerRobot {
public:
    LineFollowerRobot();

    void init();
    void moveForward(const uint32_t& speed);

private:
    MotorController* m_motorController;
    LineSensor* m_lineSensor;
};

#endif // LINEFOLLOWERROBOT_H
