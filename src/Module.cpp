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

}

bool Module::check_downstream(){

}

void Module::send_upstream(bool pause){

}

bool Module::is_hand(){

}

bool Module::e_stop(){

}