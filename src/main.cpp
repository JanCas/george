#include <Arduino.h>

#include "cppQueue.h"
#include "MotorEncoder.hpp"
#include "PID_controller.hpp"
#include "Module.hpp"
#include "Disk.hpp"
#include "Swiveler.hpp"
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>

Swiveler *swively = new Swiveler(8);
cppQueue *mm_command_queue = new cppQueue(sizeof(mm_attr), 2, FIFO, true);
PID_controller pid(.35, 0, .08, .075);
MotorEncoder motor_encoder(12,11,10, 20,21,380,12, &pid);


void print_mm(const mm_attr &mm){
    Serial.print(mm.metal);
    Serial.print(" || ");
    Serial.println(mm.right_color);
}

void move_swiveler(const mm_attr &mm_at_swiveler){
    if (mm_at_swiveler.metal){
        swively->move_to(CLOSED);
        return;
    }
    if (mm_at_swiveler.right_color){
        swively->move_to(BUCKET);
    } else {
        swively->move_to(NEXT_MODULE);
    }
}
void check_mm(){

    mm_attr *mm = new mm_attr;

    Serial.println("is it metal? ");
    while (Serial.available() == 0){}

    char x = Serial.read();
    if (x == 'y'){
        mm -> metal = true;
    }
    else if (x == 'n'){
        mm -> metal = false;
    }
    mm_command_queue->push(&mm);

    // there is an mm at the metal part
    if (mm_command_queue->getCount() > 1){
        Serial.println("Is the mm the correct color");
        mm_attr *mm_at_color = nullptr;
        mm_command_queue->peek(&mm_at_color);

        while (Serial.available() == 0){}

        x = Serial.read();

        if (x == 'y'){
            mm_at_color->right_color = true;
        }
        else if (x == 'n'){
            mm_at_color->right_color = false;
        }
   } 

    if (mm_command_queue->getCount() == 2){
        mm_attr *return_mm = nullptr;

        

        if (mm_command_queue->pop(&return_mm)){
            move_swiveler(*return_mm); 
            print_mm(*return_mm);        
        }

        delete return_mm;
    }
    Serial.println();
}


void setup()
{
    Serial.begin(9600);
    swively->init();
    // motor_encoder.set_init_speed(70);
    // motor_encoder.turn_on();
}

void loop()
{
   check_mm(); 
//    motor_encoder.drive_to(180);
}
