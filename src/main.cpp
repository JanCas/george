#include <Arduino.h>

int switch_pin = A0;
int enA = 12;
int in1 = 10;
int in2 = 11;


void setup() {
  // put your setup code here, to run once:
  pinMode(switch_pin, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // int button_state = analogRead(switch_pin);

  int button_state=1023;

  //switch is off motor should stop
  if (button_state < 1000){
    analogWrite(enA, 0);
  }else{
    analogWrite(enA, 200);
  }

}