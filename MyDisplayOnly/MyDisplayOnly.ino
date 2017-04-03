#include <Wire.h> //This library allows to communicate with I2C / TWI devices.
#include <SPI.h> //is this really necessary?
#include <Adafruit_GFX.h> //screen
#include <Adafruit_SSD1306.h> //screen

class MyDisplay
{  
  #define OLED_RESET 4
  
  
  public: MyDisplay()
  {
    Adafruit_SSD1306 display(OLED_RESET);

    #if (SSD1306_LCDHEIGHT != 64)
    #error("Height incorrect, please fix Adafruit_SSD1306.h!");
    #endif


  }

  void showSplash()
  {  
    //display
    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
    // init done
  }
};

MyDisplay screen();
void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
