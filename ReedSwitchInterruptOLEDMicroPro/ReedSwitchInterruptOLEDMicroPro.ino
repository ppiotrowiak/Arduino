//Design for micro pro
#include <Wire.h> //This library allows to communicate with I2C / TWI devices.
#include <SPI.h> //is this really necessary?
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*
 * #define is a useful C component that allows the programmer to give a name to a constant value before the program is compiled. Defined constants in arduino don't take up any program memory space on the chip. 
 * The compiler will replace references to these constants with the defined value at compile time.
 */
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

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
  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  // init done
  
  pinMode(1, INPUT_PULLUP); //interrupt pin 
  attachInterrupt(0, onStep, RISING);//dodaj przerwanie do pinu 1 (tx0) [ pin 1 is interrupt 3]
  speedFactor = circ*hour/distFact; //wstępne obliczenia

  display.clearDisplay();
  display.setCursor(10, 10);
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.print("Cycluino");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
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

  for(int i = 0; i < sizeof(speedTimes)/sizeof(long); i++)
  {
    Serial.print(speedTimes[i]);
    Serial.print(" ");
  }
  //Serial.println(sizeof(speedTimes)/sizeof(long));
  Serial.print("Speed interval: ");
  Serial.print(wheelRotationInterval);
  Serial.print(" Speed: ");
  Serial.println(speed);
  
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
