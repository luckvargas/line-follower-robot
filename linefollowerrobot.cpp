#include "linefollowerrobot.h"

LineFollowerRobot::LineFollowerRobot()
{
}

void LineFollowerRobot::init()
{
    m_motorController = new MotorController();
}

void LineFollowerRobot::moveForward(const uint32_t& speed)
{
    m_motorController->setSpeed(speed, speed);
}
