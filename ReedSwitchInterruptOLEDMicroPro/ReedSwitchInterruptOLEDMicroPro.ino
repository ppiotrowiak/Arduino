//Design for micro pro
#include <Wire.h> //This library allows to communicate with I2C / TWI devices.
#include <SPI.h> //is this really necessary?
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

volatile word steps;//load the variable from RAM and not from a storage register
volatile unsigned long speedTimes[2]; //load the variable from RAM and not from a storage register


unsigned long lastTime;
const unsigned int circ = 2073; //dystans w mm jaki pokonuje kolo w 1 obrocie zwiazane ze srednica kola. UWAGA zrobic funkcje przeliczajaca z cali w momencie uruchomienia programu
const unsigned long distFact = 1000;
const unsigned long hour = 3600000;
unsigned long speedFactor = 0;
volatile unsigned int speed = 0;
void setup()
{
  
  pinMode(1, INPUT_PULLUP); //interrupt pin 
  attachInterrupt(0, onStep, RISING);//dodaj przerwanie do pinu 1 (tx0) [ pin 1 is interrupt 3]
  speedFactor = circ*hour/distFact; //wstępne obliczenia
}

void loop()
{ 
  
  unsigned long wheelRotationInterval = speedTimes[0] - speedTimes[1];
  if ((millis() - speedTimes[0]) < 2000)
  {
    speed = speedFactor/wheelRotationInterval;
  }
  else 
  {
    speed = 0;
  } 

  
  delay(1000);

}

void onStep()
{
  //static unsigned long lastTime;
  unsigned long timeNow = millis(); //unsigned long 32 bits  range from 0 to 4,294,967,295 (2^32 - 1)
  if (timeNow - speedTimes[0] < 200) //debouncing
    return;

    speedTimes[1] = speedTimes[0];
    speedTimes[0] = timeNow;   
    
    steps++;      
}
