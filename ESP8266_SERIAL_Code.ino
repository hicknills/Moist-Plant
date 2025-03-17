
#include <SoftwareSerial.h> // Serial communication port
#include <ESP8266WiFi.h> // Wi-Fi library

// pins for ESP
const byte espRXpin = 4;
const byte espTXpin = 5;
int LED = 2; // onboard ESP LED

// WIFI information
const char* ssid     = "UTGuest";         // The SSID (name) of the Wi-Fi network you want to connect to

// Set up a new SoftwareSerial object
SoftwareSerial mySerial (espRXpin, espTXpin);

// Start with 9600 baud rate
void setup()
{
  // Define pin modes for TX and RX
  pinMode(espRXpin, INPUT);
  pinMode(espTXpin, OUTPUT);
  pinMode(LED, OUTPUT); // onboard LED
    
  // Set the baud rate for the SoftwareSerial object
  mySerial.begin(9600);

  // Connect to WIFI
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() {
  delay(3000);
  char c = mySerial.read();
  Serial.print("read: ");
  Serial.print(c);
  Serial.print(": ");
  Serial.print((int)c);
  Serial.print("\n");
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
}


