Class MyDisplay
{

/*
 * #define is a useful C component that allows the programmer to give a name to a constant value before the program is compiled. 
 * Defined constants in arduino don't take up any program memory space on the chip. 
 * The compiler will replace references to these constants with the defined value at compile time.
 */
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
  
unsigned long screenRefreshInterval = 1000;
unsigned long screenRefreshLast = 0;  

}


//to bylo w setupie
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  // init done
  
  //to tez bylo w setupie - to trzeba dac do metody "showSplash"
    display.clearDisplay();
  display.setCursor(10, 10);
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.print("Cycluino");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
  
  
  void screenRefresh()
{
  //show speed on the oled  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(3);
  if ((speed/1000) > 9)
  {
    display.setCursor(0, 10);//for speed km 10-99
  }
  else 
  {
    display.setCursor(18, 10);//for speed km0-9
  }
  display.print(speed/1000);
  //display.print("0");
  display.setCursor(30, 10);
  display.print(".");
  display.setCursor(45,10);
  int reminder = speed % 1000;
  String rem = String(reminder, DEC);
  if (rem.length() == 1)
  {
    rem = rem + "0";
  }
  else if (rem.length() > 2)
  {
    rem = rem.substring(0,2);
  }
  display.print(rem);
  display.setCursor(80, 24);
  display.setTextSize(1);
  display.print("km/h");
  

  //display cadence
  display.setTextSize(3);
  display.setCursor(45,40);
  display.print(cadence);
  display.setTextSize(1);
  display.setCursor(80,54);  
  display.print("rpm");
  display.display();
}