#include "motordriver.h"

MotorDriver::MotorDriver()
    : m_serial(m_receivePin, m_transmitPin)
    , m_roboclaw(&m_serial, m_comunicationTimeout)
{
    m_roboclaw.begin(m_boudrate);
}

void MotorDriver::setSpeed(const uint32_t& leftMotorSpeed, const uint32_t& rightMotorSpeed)
{
    m_roboclaw.SpeedM1(m_address, leftMotorSpeed);
    m_roboclaw.SpeedM2(m_address, -rightMotorSpeed);
}

Pair<uint32_t, uint32_t> MotorDriver::getSpeed()
{
    uint32_t leftMotorSpeed = m_roboclaw.ReadSpeedM1(m_address);
    uint32_t rightMotorSpeed = m_roboclaw.ReadSpeedM2(m_address);

    Pair<uint32_t, uint32_t> speed(leftMotorSpeed, rightMotorSpeed);
    return speed;
}
