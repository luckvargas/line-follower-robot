#include "linesensor.h"
#include "util/util.h"

LineSensor::LineSensor()
    : m_qtrSensors(sensorPins, NUM_SENSORS, 2500)
{
}

int LineSensor::read()
{
    int position = m_qtrSensors.readLine(m_sensorValues);

    //    if (Serial) {
    //        for (int i = 0; i < NUM_SENSORS; i++) {
    //            Serial << m_sensorValues[i] << "\t";
    //        }
    //        Serial << endl;
    //    }

    return position;
}

void LineSensor::calibrate()
{
    m_qtrSensors.calibrate();
}
