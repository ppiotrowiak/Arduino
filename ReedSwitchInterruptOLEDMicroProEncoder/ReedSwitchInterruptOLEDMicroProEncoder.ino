//Design for micro pro
#include <Wire.h> //This library allows to communicate with I2C / TWI devices.
#include <SPI.h> //is this really necessary?
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ClickEncoder.h>
#include <TimerOne.h>

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
volatile unsigned long cadenceTimes[2];
unsigned long wheelRotationInterval;

unsigned long lastTime;
unsigned long lastTimeCadence;
unsigned long screenRefreshInterval = 1000;
unsigned long screenRefreshLast = 0;
const unsigned int circ = 2073; //dystans w mm jaki pokonuje kolo w 1 obrocie zwiazane ze srednica kola. UWAGA zrobic funkcje przeliczajaca z cali w momencie uruchomienia programu
const unsigned long distFact = 1000;
const unsigned long hour = 3600000;
unsigned long speedFactor = 0;
volatile unsigned int speed = 0; //max value 65,535 (2^16) - 1)
volatile unsigned int cadence = 0;

void setup()
{
//  Serial.begin(9600);
//    while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }

//przydaloby sie tutaj zainicjowac tablice...

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  // init done
  
  //pinMode(1, INPUT_PULLUP); //interrupt pin for speed
  pinMode(7, INPUT_PULLUP); //interrupt pin for interrupts (now only for speed)
  pinMode(0, INPUT_PULLUP); //interrupt pin for cadence
  //attachInterrupt(3, onStep, RISING);//dodaj przerwanie do pinu 1 (tx0) [ pin 1 is interrupt 3]
  attachInterrupt(4, onStep, RISING);//obsluga przerwania 4 (przerwanie jest na pinie 7)
  attachInterrupt(2, onCadence, RISING);//[ pin 0 is interrupt 2] (rx1)
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
  unsigned long currentMillis = millis();
  //calculation of speed  
  if ((millis() - speedTimes[0]) < 2000)
  {
    wheelRotationInterval = speedTimes[0] - speedTimes[1];
    speed = speedFactor/wheelRotationInterval;
  }
  else 
  {
    speed = 0;
  } 

  //calculation of cadence
  if (millis() - cadenceTimes[0] < 3500)
  {
    cadence = 60000 / (cadenceTimes[0] - cadenceTimes[1]);
  }
  else 
  {
    cadence = 0;
  }
  
  if((unsigned long)(currentMillis - screenRefreshLast) >= screenRefreshInterval)
  {
    screenRefreshLast = currentMillis;
    screenRefresh();
  }
  

  /*
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
  Serial.print("Cadence: ");
  Serial.println(cadence);
  Serial.print("Cadence times: ");
  for(int i = 0; i < sizeof(speedTimes)/sizeof(long); i++)
  {
    Serial.print(cadenceTimes[i]);
    Serial.print(" ");
  }
  */
  
 
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

void onCadence()
{
  unsigned long timeNow = millis();
  if (timeNow - cadenceTimes[0] < 200) //debouncing
  return;

  cadenceTimes[1] = cadenceTimes[0];
  cadenceTimes[0] = timeNow;
}

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


