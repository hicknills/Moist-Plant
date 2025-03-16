#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// LCD setup
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo myservo;  // Create Servo object

int moistureSensor = A0;
int moistureLevel;
int pos = 0;

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    myservo.attach(10); // Attach servo to Pin 10
}

void loop() {
    moistureLevel = analogRead(moistureSensor);
    
    lcd.setCursor(0, 0);
    lcd.print("Moisture:       ");
    lcd.setCursor(0, 1);
    lcd.print(moistureLevel);

    // Send raw data to Python (no timestamp, Python will add it)
    Serial.print("{\"moisture_level\":");
    Serial.print(moistureLevel);
    Serial.print(", \"servo_position\":");

    if (moistureLevel < 300) { // Soil is too dry
        lcd.setCursor(0, 0);
        lcd.print("Watering...     ");
        lcd.setCursor(0, 1);
        lcd.print("                ");
        Serial.println("90}");

        for (pos = 0; pos <= 90; pos += 1) { 
          myservo.write(pos);
          delay(45);
        }
        delay(2000);
        for (pos = 90; pos >= 0; pos -= 1) { 
          myservo.write(pos);
          delay(45);
        }

        for (int i = 5; i > 0; i -= 1) {
          lcd.setCursor(0, 0);
          lcd.print("Restarting in...");
          lcd.setCursor(0, 1);
          lcd.print(i);
          lcd.setCursor(1, 1);
          lcd.print("               ");
          delay(1000);
        } 
    } else {
        Serial.println("0}");
        delay(5000);
    }
}
