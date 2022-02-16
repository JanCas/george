#include <Arduino.h>
#include "MotorEncoder.hpp"

MotorEncoder motor_encoder(12, 11, 10, 20, 52, 21, 53);
int speed = 0;
// int switchPin = A7;


void setup() {
  motor_encoder.set_speed(speed);
  motor_encoder.turn_on();
  
  // pinMode(switchPin, INPUT);

  Serial.begin(9600);
}

void loop() {

  // int switchVal = analogRead(switchPin);
  
  // Serial.println(switchVal);

  // if (switchVal == 1023){
  //   motor_encoder.turn_on();
  // }else {
  //   motor_encoder.turn_off();
  // }

  if (Serial.available() > 0){
    int incoming = Serial.read();
    Serial.println(incoming);

    switch (incoming){
      case 97: // letter a
        motor_encoder.cw();
        break;
      case 100: // Letter d
        motor_encoder.ccw();
        break;
      case 119: // letter w
        speed = motor_encoder.set_speed(speed + 20);
        break;
      case 115: // letter s
        speed = motor_encoder.set_speed(speed - 20);
        break;
      case 114: // letter r
        motor_encoder.write(0);
        break;
    }
  }

  /*
  Serial.print("encoder A: ");
  Serial.print(motor_encoder.encoder_a_count());
  Serial.print(" || encoder B: ");
  Serial.println(motor_encoder.encoder_b_count());
  */
}