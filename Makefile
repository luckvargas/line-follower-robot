# Arduino makefile
ifeq ($(PLATFORM), esp32)
    ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
    SKETCH = $(ROOT_DIR)/line-follower-robot.ino
    UPLOAD_PORT = /dev/ttyUSB0

    CHIP = esp32
    ESP_ROOT = $(HOME)/Arduino/hardware/espressif/esp32
    ARDUINO_LIBS_DIR = $(HOME)/Arduino/libraries

    LIBS = $(ARDUINO_LIBS_DIR)/Button \
        $(ARDUINO_LIBS_DIR)/Fuzzy \
        $(ARDUINO_LIBS_DIR)/RoboClaw \
        $(ARDUINO_LIBS_DIR)/QTRSensors \
        $(ARDUINO_LIBS_DIR)/PID \
        $(ESP_ROOT)/libraries/BluetoothSerial \
        $(ESP_ROOT)/libraries/EEPROM

    include $(HOME)/makeEspArduino/makeEspArduino.mk
else
    # Parameters for compiling
    ARDUINO_DIR     = $(HOME)/arduino-1.8.5
    AVR_TOOLS_DI    = $(HOME)/arduino-1.8.5/hardware/tools/avr
    TARGET          = output
    ARDUINO_LIBS    = StandardCplusplus Button LED RoboClaw SoftwareSerial QTRSensors Fuzzy

    # Avrdude code for programming
    AVRDUDE		= $(ARDUINO_DIR)/hardware/tools/avr/bin/avrdude
    AVRDUDE_CONF	= $(ARDUINO_DIR)/hardware/tools/avr/etc/avrdude.conf
    MONITOR_PORT        = /dev/ttyACM0
    MCU                 = atmega328p

    include /usr/share/arduino/Arduino.mk
endif
