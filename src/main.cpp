#include <Arduino.h>

#include "cppQueue.h"
#include "MotorEncoder.hpp"
#include "PID_controller.hpp"
#include "Module.hpp"
#include "Disk.hpp"
#include "Swiveler.hpp"
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>
#include <LCD.hpp>
#include <QTRSensors.h>
#include "MMQueue.hpp"

Swiveler *swively = new Swiveler(8);
cppQueue *mm_command_queue = new cppQueue(sizeof(mm_attr), 2, FIFO, true);
PID_controller pid(.35, 0, .08, .075);
MotorEncoder motor_encoder(12, 11, 10, 20, 21, 380, 12, &pid);
LCD lcd(16, 2);
int delayTime = 100;
QTRSensors qtr;

int downstream_pin = 1;
int led_pin = 2;

MMQueue mm_queue(5, (const uint8_t[]){22, 36, 24, 38, 26, 40, 28, 42, 30, 44, 32, 46, 34}, 2);

bool running = true;


void setup()
{
    Serial.begin(9600);
    motor_encoder.set_init_speed(30);
    // motor_encoder.turn_on();

    swively->init();
    swively->move_to(BUCKET);

    lcd.init();
    mm_queue.init();
    lcd.display_message("MAX:", LEFT, 0);
    lcd.display_message("5", RIGHT, 0);
    lcd.display_message("CURRENT:", LEFT, 1);
}

void loop()
{   
    if (!running){
        running = digitalRead(downstream_pin) == LOW;
        motor_encoder.turn_off();
    }
    else{
        motor_encoder.turn_on();

        int num_mm = mm_queue.num_mm_in_queue();
        lcd.display_message(String(num_mm), RIGHT, 1);

        if (num_mm > 5){
            digitalWrite(led_pin, HIGH);
        }else{
            digitalWrite(led_pin, LOW);
        }

        if (digitalRead(downstream_pin) == HIGH){
            running = false;
            return;
        }


    }

    
    

    

}  