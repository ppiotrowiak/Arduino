/*
 * Cycluino - College project by Przemyslaw Piotrowiak
 * 
 */

#include <Wire.h> //This library allows to communicate with I2C / TWI devices.
#include <SPI.h> //is this really necessary?
#include <Adafruit_GFX.h> //screen
#include <Adafruit_SSD1306.h> //screen
#include "OLEDController.h" //custom library using Adafruit's GFX and SSD1306
#include "Encoder.h" //custom library

//ustawienia cycluino
volatile word steps;//load the variable from RAM and not from a storage register
volatile unsigned long speedTimes[2]; //load the variable from RAM and not from a storage register
volatile unsigned long cadenceTimes[2];
unsigned long wheelRotationInterval;
unsigned long lastTime;
unsigned long lastTimeCadence;

const unsigned int circ = 2073; //dystans w mm jaki pokonuje kolo w 1 obrocie zwiazane ze srednica kola. UWAGA zrobic funkcje przeliczajaca z cali w momencie uruchomienia programu
const unsigned long distFact = 1000;
const unsigned long hour = 3600000;
unsigned long speedFactor = 0;
volatile unsigned int speed = 0; //max value 65,535 (2^16) - 1)
volatile unsigned int cadence = 0;


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif  


OLEDController displayController;

//settings for the display refresh
unsigned long screenRefreshInterval = 1000; //screen
unsigned long screenRefreshLast = 0;
int screenNo = 0;

//settings for the encoder
byte pushButton = 4;
byte dt = 5;
byte clk = 6;

//initialize encoder
Encoder en1(dt, clk, pushButton, 5);


void setup() {
  //put your setup code here, to run once:
  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  displayController.init(&display);  
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(en1.GetPosition());
  //sprawdzenie stanu enkodera
  if (en1.AskPosChange())
  {
    Serial.println(en1.GetPosition());
    screenNo = en1.GetPosition();
    en1.AckPosChange();   
  };
  //en1.HasRotated();
  
  //odswiezanie ekranu
  unsigned long currentMillis = millis();

  //screen refresh
  if((unsigned long)(currentMillis - screenRefreshLast) >= screenRefreshInterval)
  {
    screenRefreshLast = currentMillis;
    screenRefresh(screenNo);
  }
  delay(1);//for stability
}

void screenRefresh(int screen)
{
  if (screen < 0) {screen = screen*(-1);}

  Serial.print("Display refresh: ");
  Serial.println(screen);   
  switch(screen)
  {
    case 0:
      Serial.println("Speed&Cadence");
      displayController.showSpeedAndCadence(4000, 70);
      break;      
    case 1:
      Serial.println("Temperature&Humidity");
      displayController.showTempAndHumidity();
      break;
    case 2:
      Serial.println("Compass");
      //displayController.showCompass();
      break;
  }
}



