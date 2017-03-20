/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor

 This example code is in the public domain.
 */

class Encoder
{
	// Class member variables
	// These are initialized at startup
	int _range; // ilosc "pozycji" enkodera
	int _pinA; // pin A enkodera
	int _pinB; // pin B enkodera
	int _pinButton; // pin przycisku enkodera

	// This properties maintain current state
	int currentPosition; //aktualna "pozycja" enkodera
	int previousPosition; //poprzednia "pozycja" enkodera
	bool button; // stan przycisku
	bool posChanged = false; // wskaznik zmiany pozycji

	// Constructor - creates an encoder and intializes the members variable and state
	public: Encoder(int pinA, int pinB, int pinButton, int range)
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

		previousPosition = currentPosition = 0; // domyœlna "pozycja" enkodera to 0		
	}

	bool IsButtonPressed()
	{
		return !digitalRead(_pinButton);
	}

	void AckPosChange()
	{
		posChanged = false;
	}
};

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;
int dt = 3;
int clk = 4;

int encoder_state; //to idzie do obiektu


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  //pinMode(pushButton, INPUT);
  //pinMode(dt, INPUT);
  //pinMode(clk, INPUT);
    
  encoder_state = 3; //stan podstawowy
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  int dtState = digitalRead(dt);
  int clkState = digitalRead(clk);

  int encoder_state_temp = read_gray_code_from_encoder(dtState, clkState);
  if (encoder_state != encoder_state_temp)
  {
    encoder_rotation(encoder_state, encoder_state_temp);
    encoder_state = encoder_state_temp;
  }
    
  delay(1);        // delay in between reads for stability
}

byte read_gray_code_from_encoder(int pin1, int pin2)
{
  byte val=0;
  if (1 == pin1)
    val += 2;
  
  if (1 == pin2)
    val += 1;
    
  return val;
}

void encoder_rotation(int prev, int current)
{
  //if ((prev==3 && current==1) || (prev==0 && current==2))//clockwise
  if (prev==3 && current==1)
  {
    //licznik++;
    //Serial.println(licznik);
  }
  //else if ((prev==2 && current==0) || (prev==1 && current==3))
  else if (prev==3 && current==2)
  {
    //licznik--;
    //Serial.println(licznik);
  }
}


