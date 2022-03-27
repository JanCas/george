#include "Module.hpp"


Module::Module(COLORS target_color, MMQueue *mm_queue, ColorSensor *color_sensor, HallSensor *hall_sensor, Swiveler *swively, 
                Disk *disk, MotorEncoder *shaker_motor,int upstream_io_pin, int downstream_io_pin) {
    this->target_color = target_color;
    this->mm_queue = mm_queue;
    this->color_sensor = color_sensor;
    this->hall_sensor = hall_sensor;
    this->swively = swively;
    this->disk = disk;
    this->mm_command_queue = new cppQueue(sizeof(mm_attr), 2, FIFO, true);
    this->shaker_motor = shaker_motor;
    this->lcd = new LCD(16,2);

    pinMode(upstream_io_pin, OUTPUT);
    pinMode(downstream_io_pin, INPUT);

    this->upstream_io_pin = upstream_io_pin;
    this->downstream_io_pin = downstream_io_pin;
}

Module::Module(COLORS target_color, MMQueue *mm_queue, ColorSensor *color_sensor, Swiveler *swively, Disk *disk){
    this->target_color = target_color;
    this->mm_queue = mm_queue;
    this->color_sensor = color_sensor;
    this->swively = swively;
    this->disk = disk;
    this->mm_command_queue = new cppQueue(sizeof(mm_attr), 2, FIFO, true);
    this->lcd = new LCD(16,2);
}

Module::~Module() {
    delete mm_queue;
    delete color_sensor;
    delete hall_sensor;
    delete swively;
    delete mm_command_queue;
    delete disk;
    delete shaker_motor;
    delete lcd;
}

void Module::calibrate() {
    // all the calibration code    
}

void Module::init(){
    swively->init();
    shaker_motor->set_speed(255);
    lcd->init();
    mm_queue->init();
}

void Module::pause() {
    if (!running) return;
}

void Module::continue_module(){
    if (running) return;
}

void Module::step() {

    // check if the queue is full
    if (mm_queue->is_full() && 0){
        send_upstream(true);
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

bool Module::check_downstream(){
    return digitalRead(downstream_io_pin) == HIGH;
}

void Module::send_upstream(bool pause){
    if (pause){
        digitalWrite(upstream_io_pin, HIGH);
    }else{
        digitalWrite(upstream_io_pin, LOW);
    }
}

void Module::print_mm(const mm_attr &mm){
    Serial.print(mm.metal);
    Serial.print(" || ");
    Serial.println(mm.right_color);
}

void Module::check_mm(){

    mm_attr *mm = new mm_attr;

    mm->metal = false;
    mm_command_queue->push(&mm);

    // there is an mm at the metal part
    if (mm_command_queue->getCount() > 1){
        mm_attr *mm_at_color = nullptr;
        mm_command_queue->peek(&mm_at_color);

        COLORS color = color_sensor->get_color();
        display_mm_color(color);   

        if (color == target_color){
            mm_at_color->right_color = true;
        }
        else if (color == target_color){
            mm_at_color->right_color = false;
        }
   } 

    if (mm_command_queue->getCount() == 2){
        mm_attr *return_mm = nullptr;

        if (mm_command_queue->pop(&return_mm)){
            move_swiveler(*return_mm);
        }
        delete return_mm;
    }
    Serial.println();
}

void Module::move_swiveler(const mm_attr &mm_at_swiveler){
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

void Module::display_queue_size(int queue_size){
    lcd->clear_row(0);
    lcd->display_message(String(max_queue_size), LEFT, 0);
    lcd->display_message("||", CENTER, 0);
    lcd->display_message(String(queue_size), RIGHT, 0);
}

void Module::display_mm_color(COLORS color){
    lcd->clear_row(1);
    lcd->display_message(color_sensor->color_to_string(target_color), LEFT, 1);
    lcd->display_message("||", CENTER, 1);
    lcd->display_message(color_sensor->color_to_string(color), RIGHT, 1);    
}

// bool Module::is_hand(){

// }

// bool Module::e_stop(){

// }