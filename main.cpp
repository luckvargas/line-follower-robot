/*
Project:	line-follower-robot
MCU: Arduino Uno

Created using QtCreator
*/

#include "linefollowerrobot.h"
#include <Arduino.h>

LineFollowerRobot lineFollower;

void setup()
{
    Serial.begin(115200);
    lineFollower.init();
}

void loop()
{
    lineFollower.moveForward(0);
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
