#include "linefollowerrobot.h"
#include "fuzzycontroller.h"
#include "linesensor.h"
#include "motordriver.h"

LineFollowerRobot::LineFollowerRobot()
{
}

void LineFollowerRobot::init()
{
    m_motorDriver = new MotorDriver();
    m_lineSensor = new LineSensor();
    m_controller = new FuzzyController();
}

void LineFollowerRobot::moveForward(const uint32_t& speed)
{
    m_motorDriver->setSpeed(speed, speed);
}

void LineFollowerRobot::readSensors()
{
    m_lineSensor->read();
}

void LineFollowerRobot::follow()
{
    m_input = m_lineSensor->read();
    m_output = m_controller->evaluate(m_input);

    m_motorDriver->setSpeed(m_linearSpeed + m_output, m_linearSpeed - m_output);
}

void LineFollowerRobot::setLinearSpeed(int linearSpeed)
{
    m_linearSpeed = linearSpeed;
}
