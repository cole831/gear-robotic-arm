#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create PCA9685 object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // Min pulse length count (approx 0°)
#define SERVOMAX  600 // Max pulse length count (approx 180°)
#define SERVO_CHANNEL 0 // Servo connected to channel 0 on PCA9685

void setup() {
  Serial.begin(9600);
  Serial.println("PCA9685 Servo Test");

  pwm.begin();
  pwm.setPWMFreq(50); // Analog servos run at ~50 Hz update rate

  delay(10);
}

void loop() {
  // Sweep from 0° to 180°
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    for (int i = 0; i < 4; i++) {
      pwm.setPWM(i, 0, pulselen);
    }
    delay(2);
  }

  // Sweep back from 180° to 0°
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    for (int i = 0; i < 4; i++) {
      pwm.setPWM(i, 0, pulselen);
    }
    delay(2);
  }
}