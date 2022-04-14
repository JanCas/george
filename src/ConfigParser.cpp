#include "ConfigParser.hpp"


ConfigParser::ConfigParser(int adress, const int adress_pins[], const int sorting_color_pins[], const int queue_size_pins[]) {
    this->adress_pins = adress_pins;
    this->sorting_color_pins = sorting_color_pins;
    this->queue_size_pins = queue_size_pins;
}

ConfigParser::~ConfigParser() {
    delete []adress_pins;
    delete []sorting_color_pins;
    delete []queue_size_pins;
}

void ConfigParser::init() {
    for (int i = 0; i < 2; i++)
    {
        pinMode(adress_pins[i], INPUT);
    }   
    for (int i = 0; i < 3; i++)
    {
        pinMode(sorting_color_pins[i], INPUT);
    }   
    for (int i = 0; i < 3;i++)
    {
        pinMode(queue_size_pins[i], INPUT);
    }   
}

bool ConfigParser::read(){
    if (int_from_pins(adress_pins, 2) != adress) return false; // the message is not meant for this arduino

    int color_int = int_from_pins(sorting_color_pins, 3);
    queue_size = int_from_pins(queue_size_pins, 3);

    switch (color_int)
    {
    case 1:
        color = RED;
        break;
    case 2:
        color = GREEN;
        break;
    case 3:
        color = BLUE;
        break;
    case 4:
        color = YELLOW;
        break;
    case 5:
        color = ORANGE;
        break;
    case 6:
        color = BROWN;
        break; 
    default:
        break;
    }

    return true;
}

int ConfigParser::int_from_pins(const int *pins, int length){
    char binary[length];

    for (int i = 0; i < length; i++)
    {
        binary[i] = digitalRead(pins[i]);
    }
    return convert(binary);
}

int ConfigParser::convert(char *binary_string){
    unsigned result = 0;
    while (*binary_string)
    {
        result *= 2;
        result += *binary_string == '1' ? 1 : 0;
        ++binary_string;
    }
    return result;
}

COLORS ConfigParser::get_color(){
    return color;
}

int ConfigParser::get_queue_size(){
    return queue_size;  
}