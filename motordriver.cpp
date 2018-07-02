#include "motordriver.h"

MotorDriver::MotorDriver()
#ifdef __AVR__
    : m_serial(m_receivePin, m_transmitPin)
#else
    : m_serial(m_hardwareSerial)
#endif
    , m_roboclaw(&m_serial, m_comunicationTimeout)
{
#ifdef __AVR__
    m_serial.begin(m_boudrate, SERIAL_8N1, m_hserialRxPin, m_hserialTxPin);
#else
    m_serial.begin(m_boudrate);
#endif
}

void MotorDriver::setSpeed(const uint32_t& leftMotorSpeed, const uint32_t& rightMotorSpeed)
{
    m_roboclaw.SpeedM1(m_address, leftMotorSpeed);
    m_roboclaw.SpeedM2(m_address, -rightMotorSpeed);
}

Pair<uint32_t, uint32_t> MotorDriver::getSpeed()
{
    uint8_t status1, status2;
    bool valid1, valid2;

    uint32_t leftMotorSpeed = m_roboclaw.ReadSpeedM1(m_address, &status1, &valid1);
    uint32_t rightMotorSpeed = m_roboclaw.ReadSpeedM2(m_address, &status2, &valid2);

    Pair<uint32_t, uint32_t> speed((valid1) ? leftMotorSpeed : -1, (valid2) ? rightMotorSpeed : -1);
    return speed;
}

Pair<uint32_t, uint32_t> MotorDriver::getEncoders()
{

    uint8_t status1, status2;
    bool valid1, valid2;

    uint32_t leftMotorEncoder = m_roboclaw.ReadEncM1(m_address, &status1, &valid1);
    uint32_t rightMotorEncoder = m_roboclaw.ReadEncM2(m_address, &status2, &valid2);

    Pair<uint32_t, uint32_t> encoders((valid1) ? leftMotorEncoder : -1, (valid2) ? rightMotorEncoder : -1);
    return encoders;
}
