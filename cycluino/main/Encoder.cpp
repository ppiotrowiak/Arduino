#include "Encoder.h"



	// Constructor - creates an encoder and intializes the members variable and state
	Encoder::Encoder(byte pinA, byte pinB, byte pinButton, byte range)
	: _pinButton(pinButton), _pinA(pinA), _pinB(pinB), _range(range)
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
		currentPosition = 0; // poczÄ…tkowa "pozycja" enkodera to 0		
		//bool button; // stan przycisku
		//bool posChanged = false; // wskaznik zmiany pozycji
	}

	bool Encoder::IsButtonPressed()
	{
		return !digitalRead(_pinButton);
	}

	void Encoder::AckPosChange()
	{
		rotated = false;
	}

	bool Encoder::AskPosChange()
	{
		return rotated;
	}
	
	int Encoder::GetPosition()
	{
		return currentPosition;
	}

	bool Encoder::HasRotated()
	{
		encoder_state_temp = read_gray_code_from_encoder();
		if (encoder_state != encoder_state_temp) // if state is different it means encoder could be subject to rotation
		{
			encoder_rotation(encoder_state, encoder_state_temp);
			encoder_state = encoder_state_temp;
			return true;
		}
		return false;
	}

	byte Encoder::read_gray_code_from_encoder() //zwraca stan enkodera jako jeden z 4 stanow
	{
		byte val = 0;
		if (1 == digitalRead(_pinA))
			val += 2;

		if (1 == digitalRead(_pinB))
			val += 1;
     
		return val;
	}

	void Encoder::encoder_rotation(byte prev, byte current)
	{
		//if ((prev==3 && current==1) || (prev==0 && current==2))//clockwise
		if (prev == 3 && current == 1)
		{
			currentPosition++;
			rotated = true;			
		}
		//else if ((prev==2 && current==0) || (prev==1 && current==3))
		else if (prev == 3 && current == 2)
		{
			currentPosition--;
			rotated = true;			
		}
 	}

