#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "util/util.h"
#include <RoboClaw.h>
#include <SoftwareSerial.h>

class MotorDriver {
public:
    MotorDriver();

    void setSpeed(const uint32_t& leftMotorSpeed, const uint32_t& rightMotorSpeed);

    Pair<uint32_t, uint32_t> getSpeed();

private:
    uint32_t leftMotorSpeed;

    SoftwareSerial m_serial;
    RoboClaw m_roboclaw;

    ///< Constants
    const uint8_t m_receivePin = 10;
    const uint8_t m_transmitPin = 11;
    const uint32_t m_comunicationTimeout = 1000;
    const uint32_t m_boudrate = 115200;
    const uint8_t m_address = 0x80;
};

#endif // MOTORCONTROLLER_H
