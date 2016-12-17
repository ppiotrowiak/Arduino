//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
//volatile word steps;
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
int lastSteps = 0;
unsigned long lastTime;
unsigned long speedTimes[5];
int index = 0;

void setup()
{

  Serial.begin(9600);
  lcd.begin();
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, onStep, FALLING);
}

void loop()
{  
  lcd.clear();
  //Serial.println(steps);
  lcd.print("Obrotow :");
  lcd.print(steps);
  lcd.setCursor(0,1);
  lcd.print("last:");
  lcd.print(speedTimes[0]);
  lastSteps = steps;  
  delay(1000);

}

void onStep()
{
  //static unsigned long lastTime;
  unsigned long timeNow = millis();
  if (timeNow - lastTime < 100)
    return;
    Serial.print("Time now:");
    Serial.println(timeNow);
    speedTimes[0] = timeNow - lastTime;
    steps++;
    lastTime = timeNow;
}
