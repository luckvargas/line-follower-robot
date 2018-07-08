#ifndef ELAPSEDTIMER_H
#define ELAPSEDTIMER_H

#include <Arduino.h>

class ElapsedTimer {
public:
    ElapsedTimer() {}

    void start()
    {
        m_lastTime = millis();
        m_lastTimeMicros = micros();
    }

    long elapsed()
    {
        return millis() - m_lastTime;
    }
    long elapsedMicros()
    {
        return micros() - m_lastTimeMicros;
    }

private:
    long m_lastTime;
    long m_lastTimeMicros;
};

#endif // ELAPSEDTIMER_H
