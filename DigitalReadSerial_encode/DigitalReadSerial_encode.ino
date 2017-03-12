/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor

 This example code is in the public domain.
 */

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;
int dt = 3;
int clk = 4;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(dt, INPUT);
  pinMode(clk, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  int dtState = digitalRead(dt);
  int clkState = digitalRead(clk);
  // print out the state of the button:
  Serial.print(buttonState);
  Serial.print(dtState);
  Serial.println(clkState);
  delay(1000);        // delay in between reads for stability
}



