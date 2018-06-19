#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

HOME=../../..

SOURCES += main.cpp \ 
    linefollowerrobot.cpp \
    linesensor.cpp \
    motordriver.cpp \
    fuzzycontroller.cpp

HEADERS += \
    linefollowerrobot.h \
    linesensor.h \
    util/pair.h \
    util/util.h \
    util/streaming.h \
    util/elapsedtimer.h \
    motordriver.h \
    fuzzycontroller.h

DISTFILES += \
    Makefile

## Arduino Libraries
INCLUDEPATH = $$HOME/arduino-1.8.5/hardware/arduino/avr/cores/arduino \
    $$HOME/arduino-1.8.5/libraries/Bridge/src \
    $$HOME/arduino-1.8.5/libraries/Esplora/src \
    $$HOME/arduino-1.8.5/libraries/Ethernet/src \
    $$HOME/arduino-1.8.5/libraries/Firmata/src \
    $$HOME/arduino-1.8.5/libraries/GSM/src \
    $$HOME/arduino-1.8.5/libraries/LiquidCrystal/src \
    $$HOME/arduino-1.8.5/libraries/Robot_Control/src \
    $$HOME/arduino-1.8.5/libraries/RobotIRremote/src \
    $$HOME/arduino-1.8.5/libraries/Robot_Motor/src \
    $$HOME/arduino-1.8.5/libraries/SD/src \
    $$HOME/arduino-1.8.5/libraries/Servo/src \
    $$HOME/arduino-1.8.5/libraries/SpacebrewYun/src \
    $$HOME/arduino-1.8.5/libraries/Stepper/src \
    $$HOME/arduino-1.8.5/libraries/Temboo/src \
    $$HOME/arduino-1.8.5/libraries/TFT/src \
    $$HOME/arduino-1.8.5/libraries/WiFi/src \
    $$HOME/arduino-1.8.5/hardware/arduino/avr/libraries/EEPROM/src \
    $$HOME/arduino-1.8.5/hardware/arduino/avr/libraries/SoftwareSerial/src \
    $$HOME/arduino-1.8.5/hardware/arduino/avr/libraries/SPI/src \
    $$HOME/arduino-1.8.5/hardware/arduino/avr/libraries/Wire/src

## 3rdParty Arduino Libraries
INCLUDEPATH += $$HOME/Arduino/libraries/QTRSensors \
$$HOME/Arduino/libraries/RoboClaw \
$$HOME/Arduino/libraries/Fuzzy \
$$HOME/Arduino/libraries/Button \
$$HOME/Arduino/libraries/LED \
$$HOME/Arduino/libraries/StandardCplusplus
