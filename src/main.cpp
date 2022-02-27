#include <Arduino.h>

#include "cppQueue.h"
#include "MotorEncoder.hpp"
#include "PID_controller.hpp"
#include "Module.hpp"
#include "Disk.hpp"
#include "Swiveler.hpp"

PID_controller pid(0.368, .028, 0.0046, 0.7833, 1.0, .075);
MotorEncoder motor_encoder(12, 11, 10, 20, 21, 380, 12, &pid);
Disk disk(&motor_encoder);
cppQueue mm_command_queue(sizeof(mm_attr), 2, FIFO, true);
Swiveler swively(8);

void setup()
{
    swively.init();
    Serial.begin(9600);
    motor_encoder.set_init_speed(50);
    motor_encoder.turn_on();
}

void print_mm(mm_attr mm){
    Serial.print(mm.metal);
    Serial.print(" || ");
    Serial.println(mm.right_color);
}

void move_swiveler(mm_attr mm_at_swiveler){
    if (mm_at_swiveler.metal){
        swively.move_to(CLOSED);
        return;
    }
    if (mm_at_swiveler.right_color){
        swively.move_to(BUCKET);
    } else {
        swively.move_to(NEXT_MODULE);
    }
}

void check_mm(){
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
    mm_command_queue.push(&mm);

    if (mm_command_queue.getCount() >= 1){
        Serial.println("Is the mm the correct color");
        mm_attr mm_at_color;
        mm_command_queue.peek(&mm_at_color);

        while (Serial.available() == 0){}

        x = Serial.read();
        if (x == 'y'){
            mm_at_color.right_color = true;
        }
        else if (x == 'n'){
            mm_at_color.right_color = false;
        }
        Serial.println("The mm at the color position");
        print_mm(mm_at_color);
        Serial.println("----------------------------");
   } 

    if (mm_command_queue.getCount() == 2){
        mm_attr return_mm;

        if (mm_command_queue.pop(&return_mm)){
            Serial.println("MM AT THE SWIVELER ------------");
            print_mm(return_mm);
            Serial.println("-------------------------------");
            move_swiveler(return_mm);
        }
    }
    Serial.println();
}


void loop()
{
    Serial.println(pid.compute(motor_encoder.get_pos(), 72, 50));
    // motor_encoder.drive_to(72);
//    check_mm();
}
