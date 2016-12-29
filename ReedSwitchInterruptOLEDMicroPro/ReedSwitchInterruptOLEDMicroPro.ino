#include <Wire.h> //This library allows to communicate with I2C / TWI devices.
#include <LiquidCrystal_I2C.h>
volatile word steps;//load the variable from RAM and not from a storage register
volatile unsigned long speedTimes[5]; //load the variable from RAM and not from a storage register
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
int lastSteps = 0;
unsigned long lastTime;

int speedIndex = 0;
const unsigned int circ = 2073; //dystans w mm jaki pokonuje kolo w 1 obrocie zwiazane ze srednica kola. UWAGA zrobic funkcje przeliczajaca z cali w momencie uruchomienia programu
const unsigned long distFact = 1000;
const unsigned long hour = 3600000;
unsigned long speedFactor = 0;
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
  lcd.clear();
  
  // debugging  
  for(int i = 0; i < sizeof(speedTimes)/sizeof(long); i++)
  {
    Serial.print(speedTimes[i]);
    Serial.print(" ");
  }
  Serial.println(sizeof(speedTimes)/sizeof(long));
  Serial.println(speedIndex);
  //Serial.println(steps);
  lcd.print("Obrotow :");
  lcd.print(steps);
  lcd.setCursor(0,1);
  //lcd.print("last:");
  //lcd.print(speedTimes[0]);
  lcd.print(speedFactor/speedTimes[0]);
  lastSteps = steps;  
  delay(1000);

}

void onStep()
{
  //static unsigned long lastTime;
  unsigned long timeNow = millis();
  if (timeNow - lastTime < 200)
    return;
    //Serial.print("Time now:");
    //Serial.println(timeNow);
    speedTimes[speedIndex++] = timeNow - lastTime;
    if (speedIndex >= sizeof(speedTimes)/sizeof(long))
    {
      speedIndex = 0;
    }
    steps++;
    lastTime = timeNow;
    
}
