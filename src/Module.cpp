#include "Module.hpp"

Module::Module(COLORS target_color, MMQueue *mm_queue, ColorSensor *color_sensor, HallSensor *hall_sensor, Swiveler *swively,
               Disk *disk, ConfigParser *config_parser, HandSensor *hand_sensor, int upstream_io_pin, int downstream_io_pin)
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
    this->hand_sensor = hand_sensor;

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
    delete hopper_motor;
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
    pinMode(start_stop_button_pin, INPUT);
    pinMode(e_stop_pin, INPUT);
    pinMode(power_led, OUTPUT);
    pinMode(sorting_active_led, OUTPUT);
    pinMode(sorting_paused_led, OUTPUT);
    pinMode(sorting_disabled_led, OUTPUT);
    digitalWrite(power_led, HIGH);
    set_led(PAUSED);
}

void Module::set_led(LED_STATUS led_status){
    digitalWrite(sorting_active_led, LOW);
    digitalWrite(sorting_paused_led, LOW);
    digitalWrite(sorting_disabled_led, LOW);

    switch (led_status){
        case ACTIVE:
            digitalWrite(sorting_active_led, HIGH);
            break;
        case PAUSED:
            digitalWrite(sorting_paused_led, HIGH);
            break;
        case DISABLED:
            digitalWrite(sorting_disabled_led, HIGH);
            break;
    }
}

void Module::pause()
{
    if (!running)
        return;

    set_led(PAUSED);
    running = false;
    send_upstream_pause();
    disk->pause();
}

void Module::continue_module()
{
    if (running)
        return;

    set_led(ACTIVE);
    running = true;
    send_upstream_continue();
    disk->continue_disk();
}

void Module::wait_for_config()
{
    // if (config_parser->read()){
    //     target_color = config_parser->get_color();
    //     max_queue_size = config_parser->get_queue_size();
    //     display_top_row(0);
    //     display_bottom_row(NOT_A_COLOR);
    // }

    target_color = YELLOW;
    max_queue_size = 8;

    if (is_start_stop_button())
    {
        started = true;
        Serial.println("Was here");
        running = true;
    }
}

void Module::e_stop_pause()
{
    disk->pause();
    set_led(DISABLED);
    send_upstream_pause();

    lcd->clear();
    lcd->display_message("E - STOP", CENTER, 0);
    lcd->display_message("ACTIVATED", CENTER, 1);

    running = false;
    // once the button is pressed and e_stop is deactivated the disk will continue
    while (e_stop_activated() || !is_start_stop_button())
    {
        // Serial.print(analogRead(e_stop_pin));
        // Serial.print(" || ");
        // Serial.println(digitalRead(start_stop_button_pin));
    }

    lcd->clear();
    set_led(ACTIVE);
    running = true;
    disk->continue_disk();
}

void Module::hand_sensor_pause(){
    disk->pause();
    set_led(DISABLED);
    send_upstream_pause();

    lcd->clear();
    lcd->display_message("HAND", CENTER, 0);
    lcd->display_message("DETECTED", CENTER, 1);
    
    running = false;

    while (is_hand() || !is_start_stop_button()){
        Serial.println(is_hand());
    }

    lcd->clear();
    set_led(ACTIVE);
    running = true;
    disk->continue_disk();
}

void Module::step()
{
    if (!started)
    {
        wait_for_config();
        return;
    }

    // int queue_size = mm_queue->num_mm_in_queue();
    int queue_size = 0;
    // check if the queue is full
    if (queue_size > max_queue_size)
    {
        send_upstream_pause();
    }
    else
    {
        send_upstream_continue();
    }

    if (e_stop_activated())
    {
        Serial.println("Here");
        e_stop_pause();
    }

    // if (is_hand()){
    //     hand_sensor_pause();
    // }

    if (is_start_stop_button() && running)
    {
        pause();
    }
    else if (is_start_stop_button() && !running)
    {
        continue_module();
    }

    if (running)
    {
        // Serial.println("Running");
        if (disk->move_to_next())
        {
            // the disk has arrived at the next position and the checking can begin
            last_color = check_mm();
            display_bottom_row(last_color);
            delay(200);
            disk->reset_time();
        }
    }

    display_top_row(5);
}

bool Module::check_downstream()
{
    return digitalRead(downstream_io_pin);
}

void Module::send_upstream_pause()
{
    if (is_top)
    {
        hopper_motor->turn_off();
    }
    else
    {
        digitalWrite(upstream_io_pin, HIGH);
    }
}

void Module::send_upstream_continue()
{
    if (is_top)
    {
        hopper_motor->turn_on();
    }
    else
    {
        digitalWrite(upstream_io_pin, LOW);
    }
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

void Module::display_top_row(int queue_size)
{
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
}

void Module::display_bottom_row(COLORS color)
{
    lcd->clear_row(1);

    String color_string = color_sensor->color_to_string(color);
    color_string += "|";
    color_string += color_sensor->color_to_string(target_color);
    lcd->display_message(color_string, CENTER, 1);
}

bool Module::is_hand()
{
    return hand_sensor->is_hand();
}

bool Module::e_stop_activated()
{
    // Serial.println(analogRead(e_stop_pin));
    return analogRead(e_stop_pin) < 250;
}

bool Module::is_start_stop_button()
{
    if (digitalRead(start_stop_button_pin))
    {
        delay(100);
        return true;
    }
    return false;
}