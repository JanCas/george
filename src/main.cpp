#include <Arduino.h>

#include "cppQueue.h"
#include "MotorEncoder.hpp"
#include "PID_controller.hpp"
#include "Module.hpp"
#include "Disk.hpp"
#include "Swiveler.hpp"
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>


PID_controller pid(.5, 0.000, .07, .075);
MotorEncoder motor_encoder(12, 11, 10, 20, 21, 380, 12, &pid);
Disk disk(&motor_encoder);
cppQueue *mm_command_queue = new cppQueue(sizeof(mm_attr), 2, FIFO, true);
PID_controller pid(.35, 0, .08, .075);
MotorEncoder motor_encoder(12,11,10, 20,21,380,12, &pid);


PID pid_library(&pos, &speed, &setpoint,0.568, .028, 0.046, DIRECT);
PID_ATune pid_auto(&pos, &speed);

void setup()
{
    Serial.begin(9600);

    motor_encoder.set_init_speed(50);
    motor_encoder.set_speed_constraint(50);
    // motor_encoder.turn_on();

    pid_library.SetMode(AUTOMATIC);
    pid_library.SetOutputLimits(-50,50);
}

void loop()
{
    
    if(motor_encoder.drive_to(72)){
        motor_encoder.turn_off();
    }

    // motor_encoder.set_speed(speed);

    // if (pid_auto.Runtime()){
    //     Serial.print(pid_auto.GetKp());
    //     Serial.print(" || ");
    //     Serial.print(pid_auto.GetKd());
    //     Serial.print(" || ");
    //     Serial.print(pid_auto.GetKi());
    // }
}
