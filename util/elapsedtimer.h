#ifndef ELAPSEDTIMER_H
#define ELAPSEDTIMER_H

#include <Arduino.h>

class ElapsedTimer {
public:
    ElapsedTimer() {}

    void start()
    {
        m_lastTime = millis();
    }

    long elapsed()
    {
        return millis() - m_lastTime;
    }

private:
    long m_lastTime;
};

#endif // ELAPSEDTIMER_H
