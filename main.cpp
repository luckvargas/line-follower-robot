/*
Project:	line-follower-robot
MCU: Arduino Uno

Created using QtCreator
*/

#include <Arduino.h>

#define LED_PIN 13
#define DELAY_MS 500

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(115200);
}

void loop()
{
    Serial.println("Blink led!");

    digitalWrite(LED_PIN, HIGH);
    delay(DELAY_MS);
    digitalWrite(LED_PIN, LOW);
    delay(DELAY_MS);
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
