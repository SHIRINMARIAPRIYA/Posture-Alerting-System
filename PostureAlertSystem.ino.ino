#include <IRremote.h>

// Pin Definitions
const int irSensorPin = 2;        
const int ultrasonicTrigPin = 3;  
const int ultrasonicEchoPin = 4;  
const int buzzerPin = 5;          

long duration;                    
int distance;                     

void setup() {
  // Initialize pins
  pinMode(irSensorPin, INPUT);    
  pinMode(ultrasonicTrigPin, OUTPUT);  
  pinMode(ultrasonicEchoPin, INPUT);  
  pinMode(buzzerPin, OUTPUT);     
  
  // Start serial communication for debugging (optional)
  Serial.begin(9600);             
}

void loop() {
  // Check if the IR sensor detects a person
  int personDetected = digitalRead(irSensorPin);  
  
  if (personDetected == HIGH) {  
    // Send a pulse to the ultrasonic sensor to measure distance
    digitalWrite(ultrasonicTrigPin, LOW);  
    delayMicroseconds(2);
    digitalWrite(ultrasonicTrigPin, HIGH); 
    delayMicroseconds(10);
    digitalWrite(ultrasonicTrigPin, LOW);  
    
    // Measure the pulse duration that reflects the distance
    duration = pulseIn(ultrasonicEchoPin, HIGH); 
    distance = duration * 0.0344 / 2;  

    // Output the measured distance to the serial monitor (for debugging)
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    // Check if the user is too close to the sensor (indicating poor posture)
    if (distance < 20) {  // If the distance is less than 20 cm, user is likely hunched over
      digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer to alert the user
    } else {
      digitalWrite(buzzerPin, LOW);   // Turn off the buzzer if posture is correct
    }
  } else {
    // If no person is detected, ensure the buzzer is off
    digitalWrite(buzzerPin, LOW);
  }

  delay(500);  
}
