#include "Module.hpp"


Module::Module(COLORS target_color, MMQueue *mm_queue, ColorSensor *color_sensor, HallSensor *hall_sensor, Swiveler *swively, DashBoard *dash_board, Disk *disk) {
    this->target_color = target_color;
    this->mm_queue = mm_queue;
    this->color_sensor = color_sensor;
    this->hall_sensor = hall_sensor;
    this->swively = swively;
    this->dash_board = dash_board;
    this->disk = disk;
    this->mm_command_queue = new cppQueue(sizeof(mm_attr), 2, FIFO, true);
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
}

void Module::pause() {

}

void Module::step() {

    // check if the queue is full
    if (mm_queue->is_full()){
        // implement this later
    }

    if (check_downstream()){
        
    }

    if (is_hand()){

    }

    if (e_stop()){
        
    }

    if (disk->move_to_next()){
        // the disk has arrived at the next position and the checking can begin
        check_mm();
    }
}

// bool Module::check_downstream(){

// }

void Module::send_upstream(bool pause){

}

void Module::print_mm(mm_attr mm){
    Serial.print(mm.metal);
    Serial.print(" || ");
    Serial.println(mm.right_color);
}

void Module::check_mm(){
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
    mm_command_queue->push(&mm);

    if (mm_command_queue->getCount() >= 1){
        Serial.println("Is the mm the correct color");
        mm_attr mm_at_color;
        mm_command_queue->peek(&mm_at_color);

        while (Serial.available() == 0){}

        x = Serial.read();
        if (x == 'y'){
            mm_at_color.right_color = true;
        }
        else if (x == 'n'){
            mm_at_color.right_color = false;
        }
    } 

    if (mm_command_queue->getCount() == 2){
        mm_attr return_mm;

        if (mm_command_queue->pop(&return_mm)){
            Serial.println("MM AT THE SWIVELER ------------");
            print_mm(return_mm);
            Serial.println("-------------------------------");
            move_swiveler(return_mm);
        }
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