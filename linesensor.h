#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <QTRSensors.h>

#define NUM_SENSORS 6
#define TIMEOUT 2500
#define EMITTER_PIN 2

class LineSensor {
public:
    LineSensor();
    int read(bool print);
    void calibrate();

private:
    QTRSensorsRC* m_qtrSensors;
    unsigned int m_sensorValues[NUM_SENSORS];

    ///< Constants
    unsigned char sensorPins[NUM_SENSORS] = { 15, 21, 4, 5, 18, 19 };
};

#endif // LINESENSOR_H
