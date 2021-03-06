/*Hall effect switch + LCD test */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
int hallSensorPin = 2;
int ledPin = 13;
int state = 0;
int licznik = 0;

boolean lcdShowsON = false;

void setup() {
    // initialize the LCD
    lcd.begin();
    pinMode(ledPin, OUTPUT);
    pinMode(hallSensorPin, INPUT);
}

void loop(){
  
  state = digitalRead(hallSensorPin);
  
  if (state == LOW) {
    if (!lcdShowsON)
    {
      lcd.clear();
      lcd.print("Switch ON");
      lcd.setCursor(0,1);
      lcd.print(++licznik);
      lcdShowsON = true;
    }
    digitalWrite(ledPin, HIGH);
  }
  else {
    if (lcdShowsON)
    {
      lcd.clear();
      lcd.print("Switch OFF");
      lcd.setCursor(0,1);
      lcd.print(licznik);
      lcdShowsON = false;
    }
    digitalWrite(ledPin, LOW);
  }
}
    
