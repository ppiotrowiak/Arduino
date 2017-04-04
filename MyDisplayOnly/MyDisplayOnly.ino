#include <Wire.h> //This library allows to communicate with I2C / TWI devices.
#include <SPI.h> //is this really necessary?
#include <Adafruit_GFX.h> //screen
#include <Adafruit_SSD1306.h> //screen

class OLEDControllerClass
{
  public:
  void init(Adafruit_SSD1306* Oled1);

  private: 
  Adafruit_SSD1306* _Oled1;
};

void OLEDControllerClass::init(Adafruit_SSD1306* Oled1)
{
    _Oled1 = Oled1;
    _Oled1->begin(SSD1306_SWITCHCAPVCC, 0x3C); 
    _Oled1->clearDisplay();
    _Oled1->setCursor(10, 10);
    _Oled1->setTextColor(WHITE);
    _Oled1->setTextSize(3);
    _Oled1->print("Cycluino");
    _Oled1->display();
}
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
  



/*
    #if (SSD1306_LCDHEIGHT != 64)
    #error("Height incorrect, please fix Adafruit_SSD1306.h!");
    #endif

*/
    //display
    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
      //display->begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)



/*
  public: void showSplash()
  {  
    display->clearDisplay();
    display->setCursor(10, 10);
    display->setTextColor(WHITE);
    display->setTextSize(3);
    display->print("Cycluino");
    display->display();
    delay(2000);
    display->clearDisplay();
    display->display();

  }
  */



void setup() {
  // put your setup code here, to run once:
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
}

void loop() {
  // put your main code here, to run repeatedly:

}
