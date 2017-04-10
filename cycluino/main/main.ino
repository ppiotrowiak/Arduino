/*
 * Cycluino - College project by Przemyslaw Piotrowiak
 * 
 */

#include <Wire.h> //This library allows to communicate with I2C / TWI devices.
#include <SPI.h> //is this really necessary?
#include <Adafruit_GFX.h> //screen
#include <Adafruit_SSD1306.h> //screen
#include "OLEDController.h" //custom library using Adafruit's GFX and SSD1306
//#include "Encoder.h" //custom library

//ustawienia cycluino
volatile word steps;//load the variable from RAM and not from a storage register
volatile unsigned long speedTimes[2]; //load the variable from RAM and not from a storage register
volatile unsigned long cadenceTimes[2];
unsigned long wheelRotationInterval;
unsigned long lastTime;
unsigned long lastTimeCadence;

const unsigned int circ = 2073; //dystans w mm jaki pokonuje kolo w 1 obrocie zwiazane ze srednica kola. UWAGA zrobic funkcje przeliczajaca z cali w momencie uruchomienia programu
const unsigned long distFact = 1000;
const unsigned long hour = 3600000;
unsigned long speedFactor = 0;
volatile unsigned int speed = 0; //max value 65,535 (2^16) - 1)
volatile unsigned int cadence = 0;


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif  


OLEDController displayController;

//settings for the display refresh
unsigned long screenRefreshInterval = 1000; //screen
unsigned long screenRefreshLast = 0;
int screenNo = 0;

class Encoder
{
  // Class member variables
  // These are initialized at startup
  byte _range; // ilosc "pozycji" enkodera
  byte _pinA; // pin A enkodera
  byte _pinB; // pin B enkodera
  byte _pinButton; // pin przycisku enkodera

  // This properties maintain current state
  private: byte encoder_state; //przechowuje stan wejsc pinA i pinB
  private: byte encoder_state_temp;// = read_gray_code_from_encoder(dtState, clkState);
  private: int currentPosition; //aktualna "pozycja" enkodera
  private: bool button; // stan przycisku
  private: bool posChanged = false; // wskaznik zmiany pozycji

  // Constructor - creates an encoder and intializes the members variable and state
  public: Encoder(byte pinA, byte pinB, byte pinButton, byte range)
  {
    _range = range;
    _pinA = pinA;
    _pinB = pinB;
    _pinButton = pinButton;

    // configure input pins
    pinMode(_pinButton, INPUT);
    pinMode(_pinA, INPUT);
    pinMode(_pinB, INPUT);

    button = digitalRead(_pinButton);
    encoder_state = encoder_state_temp = read_gray_code_from_encoder();
    currentPosition = 0; // pocz�tkowa "pozycja" enkodera to 0    
  }

  bool IsButtonPressed()
  {
    return !digitalRead(_pinButton);
  }

  void AckPosChange()
  {
    posChanged = false;
  }

  bool AskPosChange()
  {
    return posChanged;
  }
  int GetPosition()
  {
    return currentPosition;
  }

  bool HasPositionChanged()
  {
    encoder_state_temp = read_gray_code_from_encoder();
    if (encoder_state != encoder_state_temp)
    {
      encoder_rotation(encoder_state, encoder_state_temp);
      encoder_state = encoder_state_temp;
      return true;
    }
    return false;
  }

  byte read_gray_code_from_encoder() //zwraca stan enkodera jako jeden z 4 stanow
  {
    byte val = 0;
    if (1 == digitalRead(_pinA))
      val += 2;

    if (1 == digitalRead(_pinB))
      val += 1;

    return val;
  }

  void encoder_rotation(byte prev, byte current)
  {
    //if ((prev==3 && current==1) || (prev==0 && current==2))//clockwise
    if (prev == 3 && current == 1)
    {
      currentPosition++;
      posChanged = true;      
    }
    //else if ((prev==2 && current==0) || (prev==1 && current==3))
    else if (prev == 3 && current == 2)
    {
      currentPosition--;
      posChanged = true;      
    }
  }
};

//settings for the encoder
byte pushButton = 4;
byte dt = 5;
byte clk = 6;

//initialize encoder
Encoder en1(dt, clk, pushButton, 5);


void setup() {
  //put your setup code here, to run once:
  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  displayController.init(&display);  
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(en1.GetPosition());
  //sprawdzenie stanu enkodera
  if (en1.AskPosChange())
  {
    Serial.println(en1.GetPosition());
    screenNo = en1.GetPosition();
    en1.AckPosChange();   
  };
  //en1.HasRotated();
  en1.HasPositionChanged();
  
  //odswiezanie ekranu
  unsigned long currentMillis = millis();

  //screen refresh
  if((unsigned long)(currentMillis - screenRefreshLast) >= screenRefreshInterval)
  {
    screenRefreshLast = currentMillis;
    screenRefresh(screenNo);
  }
  delay(1);//for stability
}

void screenRefresh(int screen)
{
  if (screen < 0) {screen = screen*(-1);}

  Serial.print("Display refresh: ");
  Serial.println(screen);   
  switch(screen)
  {
    case 0:
      Serial.println("Speed&Cadence");
      displayController.showSpeedAndCadence(4000, 70);
      break;      
    case 1:
      Serial.println("Temperature&Humidity");
      displayController.showTempAndHumidity();
      break;
    case 2:
      Serial.println("Compass");
      //displayController.showCompass();
      break;
  }
}



