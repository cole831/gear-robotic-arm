// Servo movement library
// ? to 11/7/2025 (About 1 day total work)
// Sebastian Van Deren
// Gavilan GEAR CLUB
// Robotic Arm Project - Servo Controller w/ POT's
// Code for servo controller and 3 potentiometers which are used to directly control the servos.
// This code also has readouts via serial for Pot value and PWM Length to tune the PWM length min and max of each motor

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();  // default I2C address 0x40
//SDA to A4
// Servo min and max pulse lengths (adjust to your servos)
#define SERVOMIN  155  // (CONFIRMED ROUGH LIMIT) corresponds to 0°
#define SERVOMAX  550  // (CONFIRMED LIMIT) corresponds to 180°

void setup() {
  Serial.begin(9600); //Serial Debug
  Serial.println("\nPCA9685 Servo Test"); //Serial Debug
  //delay(200); // let power stabilize (Uneccecary)
  pwm.begin();
  pwm.setPWMFreq(50); // Analog servos run at ~50 Hz update rate
  delay(10); //Give board time to start
  //You do not define analog pins
  
}
//PWM Func
void moveServo(uint8_t servoNum, int sensorValue) {
  int pulseLen = map(sensorValue, 0, 1023, SERVOMIN, SERVOMAX);  //Map ADC to Servo units (0-180 degrees)
  // Send to PCA9685 (12-bit range: 0–4095)
  pwm.setPWM(servoNum, 0, pulseLen);
}

//Vars
int sensorValue0 = 0; //POT1 on A0
int sensorValue1 = 0; //POT2 on A1
int sensorValue2 = 0; //POT3 on A2
int sensorValue3 = 0; //POT4 on A3

void loop() {
  // Read pots
  sensorValue0 = analogRead(A0); //Read POT
  //int sensorValue0 = map(sensorValue0, 0, 1023, 0, 180); //Map ADC to 180 degrees
  moveServo(0, sensorValue0); //Send to controller

  sensorValue1 = analogRead(A1);
  int pulseLen = map(sensorValue1, 0, 1023, SERVOMIN, SERVOMAX);
  Serial.print("A1: ");
  Serial.print(sensorValue1);
  Serial.print("   PWM LENG: ");
  Serial.println(pulseLen);
  moveServo(1, sensorValue1); //Send to controller


  sensorValue2 = analogRead(A2);
  moveServo(2, sensorValue2); //Send to controller

  sensorValue3 = analogRead(A3);
  moveServo(3, sensorValue3); //Send to controller

}
