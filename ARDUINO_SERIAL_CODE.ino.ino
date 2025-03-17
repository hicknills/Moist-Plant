#include <SoftwareSerial.h>

const byte unoRXpin = 6;
const byte unoTXpin = 7;

// Set up a new SoftwareSerial object
SoftwareSerial mySerial (unoRXpin, unoTXpin);

// Start with 9600 baud rate
void setup()
{
  // Define pin modes for TX and RX
    pinMode(unoRXpin, INPUT);
    pinMode(unoTXpin, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT); // onboard LED
    
    // Set the baud rate for the SoftwareSerial object
    mySerial.begin(9600);
    Serial.begin(9600);
}

void loop() {
  // write ASCII chars
  for(int i = 33; i <= 126; i++) {
    delay(3000);
    char c = (char)i;
    Serial.print(i);
    Serial.print(" ");
    Serial.print(c);
    Serial.print("\n");
    mySerial.write(c); // Write to ESP
  }

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
}