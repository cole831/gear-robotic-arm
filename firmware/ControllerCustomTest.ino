// Servo movement library
// ? to ? (about a week)
// Sebastian Van Deren
// Gavilan GEAR CLUB
// Robotic Arm Project - Servo Controller
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();  // default I2C address 0x40

// Servo min and max pulse lengths (adjust to your servos)
#define SERVOMIN  150  // corresponds to 0°
#define SERVOMAX  600  // corresponds to 180°

void setup() {
  Serial.begin(9600);
  Serial.println("PCA9685 Servo Controller");

  pwm.begin();
  pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz
  delay(10);
}

// Helper: angle (0–180) → pulse length
uint16_t angleToPulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void loop() {
  // Example sweep for 4 servos on channels 0–3
  for (int angle = 0; angle <= 180; angle += 5) {
    for (int i = 0; i < 4; i++) {
      pwm.setPWM(i, 0, angleToPulse(angle));
    }
    delay(30);
  }

  for (int angle = 180; angle >= 0; angle -= 5) {
    for (int i = 0; i < 4; i++) {
      pwm.setPWM(i, 0, angleToPulse(angle));
    }
    delay(30);
  }
}
