#include "Module.hpp"


Module::Module(COLORS target_color, MMQueue *mm_queue, ColorSensor *color_sensor, HallSensor *hall_sensor, Swiveler *swively, DashBoard *dash_board, Disk *disk, MotorEncoder *shaker_motor) {
    this->target_color = target_color;
    this->mm_queue = mm_queue;
    this->color_sensor = color_sensor;
    this->hall_sensor = hall_sensor;
    this->swively = swively;
    this->dash_board = dash_board;
    this->disk = disk;
    this->mm_command_queue = new cppQueue(sizeof(mm_attr), 2, FIFO, true);
    this->shaker_motor = shaker_motor;
}



Module::~Module() {
    delete mm_queue;
    delete color_sensor;
    delete hall_sensor;
    delete swively;
    delete dash_board;
    delete mm_command_queue;
}

void Module::calibrate() {
    // all the calibration code    
}

void Module::init(){
    swively->init();
    shaker_motor->set_speed(255);
}

void Module::pause() {

}

void Module::step() {

    // check if the queue is full
    if (mm_queue->is_full() && 0){
        // implement this later
    }

    if (check_downstream() && 0){
        
    }

    if (is_hand() && 0){

    }

    if (e_stop() && 0){
        
    }

    if (disk->move_to_next()){
        // the disk has arrived at the next position and the checking can begin
        check_mm();
    }
}

// bool Module::check_downstream(){

// }

// void Module::send_upstream(bool pause){

// }

void Module::print_mm(mm_attr mm){
    Serial.print(mm.metal);
    Serial.print(" || ");
    Serial.println(mm.right_color);
}

void Module::check_mm(){

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

        print_mm(*mm);

        if (mm_command_queue->pop(&return_mm)){
            move_swiveler(*return_mm);         
        }

        delete return_mm;
    }
    Serial.println();
}

void Module::move_swiveler(mm_attr mm_at_swiveler){
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

// bool Module::is_hand(){

// }

// bool Module::e_stop(){

// }