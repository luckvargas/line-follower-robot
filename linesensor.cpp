#include "linesensor.h"
#include "util/util.h"

LineSensor::LineSensor()
{
    m_qtrSensors = new QTRSensorsRC(sensorPins, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
    m_qtrSecondSensor = new QTRSensorsRC(SecondSensorPins, NUM_SECOND_SENSOR, SECOND_SENSOR_TIMEOUT);
}

float LineSensor::read(bool print)
{
    float position = 0;
    if (m_calibrated) {
        position = m_qtrSensors->readLine(m_sensorValues, QTR_EMITTERS_ON, WHITE_LINE);
        position = map(position, 0, (NUM_SENSORS - 1) * 1000, -10, 10);
    } else {
        position = this->readLine();
    }

    if (print) {
        for (int i = 0; i < NUM_SENSORS; i++) {
            Serial << m_sensorValues[i] << "\t";
        }
        Serial << " - Position: " << position << endl;
    }

    return position;
}

bool LineSensor::readStopSensor()
{
    unsigned int sensorValue = 0;
    // Read raw sensor values
    if (m_calibrated) {
        m_qtrSecondSensor->readCalibrated(m_secondSensorValues);
    } else {
        m_qtrSecondSensor->read(m_secondSensorValues);
    }

    // print the sensor values as numbers from 0 to 2500, where 0 means maximum reflectance and
    // 2500 means minimum reflectance

    for (unsigned char i = 0; i < NUM_SECOND_SENSOR; i++) {
        if (m_secondSensorValues[i] <= 500 && (millis() - m_readTime) > 200) {
            Serial << "Stop Sensor true" << endl;
            m_readTime = millis();
            return true;
        }
    }

    return false;
}

void LineSensor::calibrate()
{
    m_qtrSensors->calibrate();
    m_qtrSecondSensor->calibrate();
    m_calibrated = true;
}

float LineSensor::readLine()
{
    float position = 0;
    float sum = 0;
    m_qtrSensors->read(m_sensorValues);
    for (int i = 0; i < NUM_SENSORS; i++) {
        position += (i * TIMEOUT) * (TIMEOUT - m_sensorValues[i]);
        sum += (TIMEOUT - m_sensorValues[i]);
    }
    if (sum == 0)
        return 0;
    position = position / sum - TIMEOUT * (NUM_SENSORS - 1) / 2;
    position = (position / (TIMEOUT * (NUM_SENSORS - 1) / 2)) * 10;

    return position;
}

float LineSensor::map(float x,
    float in_min,
    float in_max,
    float out_min,
    float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
