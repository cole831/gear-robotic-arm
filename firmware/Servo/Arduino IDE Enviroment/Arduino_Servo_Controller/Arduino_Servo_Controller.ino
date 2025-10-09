// Servo movement library
// 10-4-2025 to 10-6-2025
// Sebastian Van Deren
// Gavilan GEAR CLUB
// Robotic Arm Project - Servo Control

#include <Servo.h>

Servo myservo;  // create servo object to control a servo when attached pins 9 and 10 will be unavaliable
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
const int buttonPin = 8;
const int RledPin = 13;
const int GledPin = 12;
int switchState = 1;


void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  //servo.attach(pin, min, max)
  pinMode(buttonPin, INPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(RledPin, OUTPUT);
}

void loop() {
  /*int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    if (switchState == 1)
      switchState = 0; // update the state
    else
      switchState = 1; // update the state
  }
  if (switchState == 1){ */
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees in steps of 1 degree
      
      digitalWrite(RledPin, LOW);
      digitalWrite(GledPin, HIGH);
      Serial.print("R-Pos:");
      Serial.print(pos);
      Serial.print(" - ");
      Serial.println("C-Pos:");
      Serial.println(myservo.read());
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(20);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, LOW);
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  /*} 
  else {
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
  }*/
}

//myservo.writeMicroseconds(1500);  
//servo.read()
