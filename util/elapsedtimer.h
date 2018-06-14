#ifndef ELAPSEDTIMER_H
#define ELAPSEDTIMER_H

#include <Arduino.h>

class ElapsedTimer {
public:
    ElapsedTimer() {}

    void ElapsedTimer::start()
    {
        m_lastTime = millis();
    }

    long ElapsedTimer::elapsed()
    {
        return millis() - m_lastTime;
    }

private:
    long m_lastTime;
};

#endif // ELAPSEDTIMER_H
