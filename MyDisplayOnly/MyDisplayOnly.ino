#include <Wire.h> //This library allows to communicate with I2C / TWI devices.
#include <SPI.h> //is this really necessary?
#include <Adafruit_GFX.h> //screen
#include <Adafruit_SSD1306.h> //screen

class MyDisplay
{  
  #define OLED_RESET 4

  private:   Adafruit_SSD1306 *display;
  
  public: MyDisplay()
  { 
    display = new Adafruit_SSD1306(OLED_RESET);

    #if (SSD1306_LCDHEIGHT != 64)
    #error("Height incorrect, please fix Adafruit_SSD1306.h!");
    #endif

    //display
    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
      display->begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
    // init done
  }

  void showSplash()
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
};

MyDisplay screen();
void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
