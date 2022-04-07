#include "ConfigParser.hpp"


ConfigParser::ConfigParser(const int adress_pins[], const int sorting_color_pins[], const int queue_size_pins[]) {
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
    for (int i = 0; i < sizeof(adress_pins)/sizeof(int); i++)
    {
        pinMode(adress_pins[i], INPUT);
    }   
    for (int i = 0; i < sizeof(sorting_color_pins)/sizeof(int); i++)
    {
        pinMode(sorting_color_pins[i], INPUT);
    }   
    for (int i = 0; i < sizeof(queue_size_pins)/sizeof(int); i++)
    {
        pinMode(queue_size_pins[i], INPUT);
    }   
}

bool ConfigParser::read(int adress){
    if (int_from_pins(adress_pins) != adress) return false; // the message is not meant for this arduino

    long int color_int = int_from_pins(sorting_color_pins);
    queue_size = int_from_pins(queue_size_pins);

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

long int ConfigParser::int_from_pins(const int *pins){
    String binary = "";

    for (int i = 0; i < sizeof(pins)/sizeof(int); i++)
    {
        if (digitalRead(pins[i]) == HIGH){
            binary += "1";
        }else{
            binary += "0";
        }
    }
    
    char binary_char[binary.length()];
    binary.toCharArray(binary_char, binary.length());


    return strtol(binary_char, NULL, 2);
}

COLORS ConfigParser::get_color(){
    return color;
}

int ConfigParser::get_queue_size(){
    return queue_size;  
}