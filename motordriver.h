#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "util/util.h"
#include <RoboClaw.h>

#ifdef __AVR__
#include <SoftwareSerial.h>
else
#include <HardwareSerial.h>
#endif

    class MotorDriver {
public:
    MotorDriver();

    void setSpeed(const uint32_t& leftMotorSpeed, const uint32_t& rightMotorSpeed);

    Pair<uint32_t, uint32_t> getSpeed();
    Pair<uint32_t, uint32_t> getEncoders();

private:
    uint32_t leftMotorSpeed;

#ifdef __AVR__
    SoftwareSerial m_serial;
#else
    HardwareSerial m_serial;
#endif

    RoboClaw m_roboclaw;

    ///< Constants
    const uint8_t m_receivePin = 10;
    const uint8_t m_transmitPin = 11;
    const uint32_t m_comunicationTimeout = 1000;
    const uint32_t m_boudrate = 115200;
    const uint8_t m_address = 0x80;

    ///< HardwareSerial Config
    const uint8_t m_hardwareSerial = 2;
    const uint8_t m_hserialRxPin = 16;
    const uint8_t m_hserialTxPin = 17;
};

#endif // MOTORCONTROLLER_H
