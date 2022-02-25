#include <Arduino.h>

#include "cppQueue.h"
#include "MotorEncoder.hpp"
#include "PID_controller.hpp"
#include "Module.hpp"

cppQueue queue(sizeof(mm_attr), 2, FIFO, true);
MotorEncoder motor_encoder(12, 11, 10, 20, 21, 380, 12);
PID_controller pid(50.0, .3, 1.0, 1.0, 1.0, .75);

void setup()
{
    Serial.begin(9600);
    // motor_encoder.set_speed(30);
    // motor_encoder.turn_on();
}


void print_mm(mm_attr mm){
    Serial.print(mm.metal);
    Serial.print(" || ");
    Serial.println(mm.right_color);
}

void loop()
{
    mm_attr mm;

    Serial.println("is it metal? ");
    while (Serial.available() == 0){

    }

    char x = Serial.read();
    if (x == 'y'){
        mm.metal = true;
    }
    else if (x == 'n'){
        mm.metal = false;
    }
    Serial.println("a new mm with determined metal value has been added to the queue");
    queue.push(&mm);

    if (queue.getCount() >= 1){
        Serial.println("Is the mm the correct color");
        mm_attr mm_at_color;
        queue.peek(&mm_at_color);

        while (Serial.available() == 0){}

        x = Serial.read();
        if (x == 'y'){
            mm_at_color.right_color = true;
        }
        else if (x == 'n'){
            mm_at_color.right_color = false;
        }
    } 

    if (queue.getCount() == 2){
        mm_attr return_mm;

        if (queue.pop(&return_mm)){
            Serial.println("MM AT THE SWIVELER ------------");
            print_mm(return_mm);
            Serial.println("-------------------------------");
        }
    }
    Serial.println();
    // Serial.println(motor_encoder.get_pos());
    // Serial.println(pid.compute(motor_encoder.get_pos(), 72));
}
