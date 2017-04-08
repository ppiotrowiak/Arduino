#include <Wire.h> //This library allows to communicate with I2C / TWI devices.
#include <SPI.h> //is this really necessary?
#include <Adafruit_GFX.h> //screen
#include <Adafruit_SSD1306.h> //screen
#include "OLEDController.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif  

OLEDController controller;

void setup() {
  // put your setup code here, to run once:

  controller.init(&display);
  controller.showSpeedAndCadence(3000, 70);
}

void loop() {
  // put your main code here, to run repeatedly:

}
