#include <LiquidCrystal_I2C.h>

// Define pins for the ultrasonic sensor
const int trigPin = 13;
const int echoPin = 12;

// Define pins for LEDs
const int ledPins[] = {10, 9, 8, 7, 6, 5}; // Change according to your wiring
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  lcd.begin();

  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize LED pins
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Start with LEDs off
  }
}

void loop() {
  // Measure distance
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm

  // Debugging: Print distance
  Serial.println(distance);
  lcd.setCursor(0,0);
  lcd.print(distance);

  // Determine the number of LEDs to light up based on distance
  int ledsToLight = map(distance, 2, 50, numLeds, 0); // Map 5-50 cm to all LEDs
  ledsToLight = constrain(ledsToLight, 0, numLeds);

  // Turn on the corresponding number of LEDs
  for (int i = 0; i < numLeds; i++) {
    if (i < ledsToLight) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }

  delay(100); // Short delay to stabilize readings
}



