#include "linesensor.h"
#include "util/util.h"

LineSensor::LineSensor()
{
    m_qtrSensors = new QTRSensorsRC(sensorPins, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
}

int LineSensor::read(bool print)
{
    int position = m_qtrSensors->readLine(m_sensorValues);

    if (print) {
        for (int i = 0; i < NUM_SENSORS; i++) {
            Serial << m_sensorValues[i] << "\t";
        }
        Serial << endl;
    }

    return position;
}

void LineSensor::calibrate()
{
    m_qtrSensors->calibrate();
}
