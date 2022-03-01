#include <Arduino.h>

#include "cppQueue.h"
#include "MotorEncoder.hpp"
#include "PID_controller.hpp"
#include "Module.hpp"
#include "Disk.hpp"
#include "Swiveler.hpp"
#include <PID_v1.h>

PID_controller pid(0.368, .028, 0.0046, 0.7833, 1.0, .075);
MotorEncoder motor_encoder(12, 11, 10, 20, 21, 380, 12, &pid);
Disk disk(&motor_encoder);
cppQueue *mm_command_queue = new cppQueue(sizeof(mm_attr), 2, FIFO, true);
Swiveler swively(8);

double speed;
double pos = 0;
double setpoint = 72;

PID pid_library(&pos, &speed, &setpoint,0.568, .028, 0.046, DIRECT);

void setup()
{
    swively.init();
    Serial.begin(9600);
   motor_encoder.set_init_speed(50);
   // motor_encoder.turn_on();

    pid_library.SetMode(AUTOMATIC);
    pid_library.SetOutputLimits(-50,50);
}

void loop()
{
    // double curr_pos = 0;
    // double new_vel = pid.compute(motor_encoder.get_pos(), 72, 30);
    // double new_vel2 = motor_encoder.pid_compute(72,30);  
    

   pos = motor_encoder.get_pos();

    if(pid_library.Compute()){
        Serial.print(speed);
        motor_encoder.set_speed(speed);
        // pos++;
        Serial.print(" || ");
        Serial.println(pos);
    }

    // Serial.print("outside_vel: ");
    // Serial.print(new_vel2);
    // Serial.print(" || inside vel: ");
    // Serial.println(new_vel2);

    //motor_encoder.set_speed(new_vel);
    //motor_encoder.drive_to(72);
}
