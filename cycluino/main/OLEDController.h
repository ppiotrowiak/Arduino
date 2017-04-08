#include "Arduino.h"
#include <Adafruit_SSD1306.h> 

#ifndef OLEDController_h
#define OLEDController_h
/*
The core of the header file consists of a line for each function in the library, 
wrapped up in a class along with any variables you need:
*/
class OLEDController
{
  public:
  void init(Adafruit_SSD1306* Oled1);
  void showSpeedAndCadence(unsigned int speed, unsigned int cadence);
 
  private: 
  Adafruit_SSD1306* _Oled1;
};



#endif

