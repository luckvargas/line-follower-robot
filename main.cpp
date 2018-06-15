/*
Project:	line-follower-robot
MCU: Arduino Uno

Created using QtCreator
*/

#include "linefollowerrobot.h"
#include "util/util.h"
#include <Arduino.h>

LineFollowerRobot lineFollower;
ElapsedTimer timer;

void setup()
{
    Serial.begin(115200);
    lineFollower.init();
}

void loop()
{
    timer.start();
    lineFollower.moveForward(0);
    lineFollower.readSensors();
    // Serial << timer.elapsed() << endl;
}

int main()
{
    // Initialize Arduino Librairies
    init();
    setup();
    while (1) {
        loop();
    }
}
