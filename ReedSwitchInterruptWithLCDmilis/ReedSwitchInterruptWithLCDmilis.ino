//Design for nano 3.0 (328)
#include <Wire.h> //This library allows to communicate with I2C / TWI devices.
#include <LiquidCrystal_I2C.h>
volatile word steps;//load the variable from RAM and not from a storage register
volatile unsigned long speedTimes[2]; //load the variable from RAM and not from a storage register
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long lastTime;
const unsigned int circ = 2073; //dystans w mm jaki pokonuje kolo w 1 obrocie zwiazane ze srednica kola. UWAGA zrobic funkcje przeliczajaca z cali w momencie uruchomienia programu
const unsigned long distFact = 1000;
const unsigned long hour = 3600000;
unsigned long speedFactor = 0;
unsigned int speed = 0;
void setup()
{

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, onStep, RISING);//dodaj przerwanie do pinu 2 
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
  
  display.clearDisplay();  
  display.setCursor(10, 10);
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.print(speed);
 
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
  
  lcd.print("Obrotow :");
  lcd.print(steps);
  lcd.setCursor(0,1);
 
  lcd.print(speed / 1000); 
  lcd.print(".");
  lcd.print(speed % 1000);
  lcd.print(" km/h");
  
  delay(1000);

}

void onStep()
{
  //static unsigned long lastTime;
  unsigned long timeNow = millis(); //unsigned long 32 bits  range from 0 to 4,294,967,295 (2^32 - 1)
  if (timeNow - speedTimes[0] < 200) //debouncing
    return;
    //Serial.print("Time now:");
    //Serial.println(timeNow);
    speedTimes[1] = speedTimes[0];
    speedTimes[0] = timeNow;   
    
    steps++;      
}
