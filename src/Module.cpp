#include "Module.hpp"

Module::Module(COLORS target_color, MMQueue *mm_queue, ColorSensor *color_sensor, HallSensor *hall_sensor, Swiveler *swively,
               Disk *disk, ConfigParser *config_parser,int upstream_io_pin, int downstream_io_pin)
{
    this->target_color = target_color;
    this->mm_queue = mm_queue;
    this->color_sensor = color_sensor;
    this->hall_sensor = hall_sensor;
    this->swively = swively;
    this->disk = disk;
    this->mm_command_queue = new cppQueue(sizeof(mm_attr), 2, FIFO, true);
    this->lcd = new LCD(16, 2);
    this->config_parser = config_parser;

    this->upstream_io_pin = upstream_io_pin;
    this->downstream_io_pin = downstream_io_pin;
    running = true;
    started = false;

    num_sorted = 0;
    num_unsorted = 0;
    num_contaminants = 0;
}

Module::~Module()
{
    delete mm_queue;
    delete color_sensor;
    delete hall_sensor;
    delete swively;
    delete mm_command_queue;
    delete disk;
    // delete shaker_motor;
    delete lcd;
    delete config_parser;
}

void Module::calibrate()
{
    disk->drive_to_zero();
}

void Module::init()
{
    swively->init();
    lcd->init();
    mm_queue->init();
    hand_sensor->init();
    disk->init();
    pinMode(upstream_io_pin, OUTPUT);
    pinMode(downstream_io_pin, INPUT);
}

void Module::pause()
{
    if (!running)
        return;

    digitalWrite(led_pause_pin, HIGH);
    running = false;
    disk->pause();
}

void Module::continue_module()
{
    if (running)
        return;

    digitalWrite(led_pause_pin, LOW);
    running = true;
    disk->continue_disk();
}

void Module::wait_for_config(){
    if (config_parser->read()){
        target_color = config_parser->get_color();
        max_queue_size = config_parser->get_queue_size();
        display_lcd(NOT_A_COLOR, 0);
    }

    if (digitalRead(start_stop_button_pin)){
        started = true;
    }
}

void Module::step()
{

    if (!started){
        wait_for_config();
        return;
    }

    int queue_size = mm_queue->num_mm_in_queue();

    // check if the queue is full
    if (queue_size > max_queue_size && 0)
    {
        send_upstream(true);
    }

    if (check_downstream() || e_stop() || is_hand() && 0)
    {
        pause();
    }
    else
    {
        continue_module();
    }

    if (running)
    {
        if (disk->move_to_next())
        {
            // the disk has arrived at the next position and the checking can begin
            last_color = check_mm(); 
            delay(1000);
            disk->reset_time();
        }
    }

    display_lcd(last_color, queue_size);
}

bool Module::check_downstream()
{
    return digitalRead(downstream_io_pin) == HIGH;
}

void Module::send_upstream(bool pause)
{
    if (pause)
    {
        digitalWrite(upstream_io_pin, HIGH);
    }
    else
    {
        digitalWrite(upstream_io_pin, LOW);
    }
}

void Module::print_mm(const mm_attr &mm)
{
    Serial.print(mm.metal);
    Serial.print(" || ");
    Serial.println(mm.right_color);
}

COLORS Module::check_mm()
{

    COLORS return_color = NOT_A_COLOR;

    mm_attr *mm = new mm_attr;

    mm->metal = false;
    mm_command_queue->push(&mm);

    // there is an mm at the metal part
    if (mm_command_queue->getCount() > 1)
    {
        mm_attr *mm_at_color = nullptr;
        mm_command_queue->peek(&mm_at_color);

        COLORS color = color_sensor->get_color();
        return_color = color;

        if (color == target_color)
        {
            mm_at_color->right_color = true;
        }
        else if (color == target_color)
        {
            mm_at_color->right_color = false;
        }
    }

    if (mm_command_queue->getCount() == 2)
    {
        mm_attr *return_mm = nullptr;

        if (mm_command_queue->pop(&return_mm))
        {
            move_swiveler_and_update_counts(*return_mm);
        }
        delete return_mm;
    }

    return return_color;
}

void Module::move_swiveler_and_update_counts(const mm_attr &mm_at_swiveler)
{
    if (mm_at_swiveler.metal)
    {
        swively->move_to(CLOSED);
        num_contaminants++;
        return;
    }
    if (mm_at_swiveler.right_color)
    {
        swively->move_to(BUCKET);
        num_sorted++;
    }
    else
    {
        swively->move_to(NEXT_MODULE);
        num_unsorted++;
    }
}

void Module::display_queue_size(int queue_size)
{
    lcd->clear_row(0);
    lcd->display_message(String(max_queue_size), LEFT, 0);
    lcd->display_message("||", CENTER, 0);
    lcd->display_message(String(queue_size), RIGHT, 0);
}

void Module::display_mm_color(COLORS color)
{
    lcd->clear_row(1);
    lcd->display_message(color_sensor->color_to_string(target_color), LEFT, 1);
    lcd->display_message("||", CENTER, 1);
    lcd->display_message(color_sensor->color_to_string(color), RIGHT, 1);
}

void Module::display_lcd(COLORS color, int queue_size)
{
    lcd->clear_row(1);

    String queue_string = String(queue_size);
    queue_string += "|";
    queue_string += String(max_queue_size);
    lcd->display_message(queue_string, LEFT, 0);

    String sorted_string = String(num_sorted);
    sorted_string += "|";
    sorted_string += String(num_unsorted);
    sorted_string += "|";
    sorted_string += String(num_contaminants);
    lcd->display_message(sorted_string, RIGHT, 0);

    String color_string = color_sensor->color_to_string(color);
    color_string += "|";
    color_string += color_sensor->color_to_string(target_color);
    lcd->display_message(color_string, CENTER, 1);
}

bool Module::is_hand()
{
    return hand_sensor->is_hand();
}

bool Module::e_stop()
{
    return digitalRead(e_stop_pin) == LOW;
}