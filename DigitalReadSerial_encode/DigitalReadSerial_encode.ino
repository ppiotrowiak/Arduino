/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor

 This example code is in the public domain.
 */

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
		currentPosition = 0; // pocz¹tkowa "pozycja" enkodera to 0		
	}

	bool IsButtonPressed()
	{
		return !digitalRead(_pinButton);
	}

	void AckPosChange()
	{
		posChanged = false;
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
			Serial.println(currentPosition);
		}
		//else if ((prev==2 && current==0) || (prev==1 && current==3))
		else if (prev == 3 && current == 2)
		{
			currentPosition--;
			Serial.println(currentPosition);
		}
	}
};

// digital pin 2 has a pushbutton attached to it. Give it a name:
byte pushButton = 2;
byte dt = 3;
byte clk = 4;

Encoder en1(dt, clk, pushButton, 5);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);    
  
}

// the loop routine runs over and over again forever:
void loop() {
  
	en1.HasPositionChanged();
      
  delay(1);        // delay in between reads for stability
}






