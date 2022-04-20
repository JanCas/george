#include "ColorSensor.hpp"
#include "config/color_sensor_values_2.h"

ColorSensor::ColorSensor(int red_pin, int green_pin, int blue_pin, int analogPin)
{
    this->red_pin = red_pin;
    this->green_pin = green_pin;
    this->blue_pin = blue_pin;

    this->analogPin = analogPin;

    pinMode(red_pin, OUTPUT);
    pinMode(green_pin, OUTPUT);
    pinMode(blue_pin, OUTPUT);

    digitalWrite(red_pin, LOW);
    digitalWrite(green_pin, LOW);
    digitalWrite(blue_pin, LOW);
}

ColorSensor::~ColorSensor()
{
}

COLORS ColorSensor::get_color()
{
    sense();
    int r = rgb_arr[0];
    int g = rgb_arr[1];
    int b = rgb_arr[2];


    Serial.print(r);
    Serial.print(" || ");

    Serial.print(g);
    Serial.print(" || ");
    Serial.println(b);

    if (is_red(r, g, b))
    {
        return RED;
    }
    else if (is_green(r, g, b))
    {
        return GREEN;
    }
    else if (is_blue(r, g, b))
    {
        return BLUE;
    }
    else if (is_brown(r, g, b))
    {
        return BROWN;
    }
    else if (is_yellow(r, g, b))
    {
        return YELLOW;
    }
    else if (is_orange(r, g, b))
    {
        return ORANGE;
    }
    return NOT_A_COLOR;
}

bool ColorSensor::is_red(int r, int g, int b)
{
    return (r > r_red_low && r < r_red_high) && 
            (g > r_green_low && g < r_green_high) && 
            (b > r_blue_low && b < r_blue_high);
}

bool ColorSensor::is_blue(int r, int g, int b)
{
    return (r > b_red_low && r < b_red_high) && 
            (g > b_green_low && g < b_green_high) && 
            (b > b_blue_low && b < b_blue_high);
}

bool ColorSensor::is_green(int r, int g, int b)
{
    return (r > g_red_low && r < g_red_high) && 
            (g > g_green_low && g < g_green_high) && 
            (b > g_blue_low && b < g_blue_high);
}

bool ColorSensor::is_brown(int r, int g, int b)
{
    return (r > br_red_low && r < br_red_high) && 
            (g > br_green_low && g < br_green_high) && 
            (b > br_blue_low && b < br_blue_high);
}

bool ColorSensor::is_yellow(int r, int g, int b)
{
    return (r > y_red_low && r < y_red_high) && 
            (g > y_green_low && g < y_green_high) && 
            (b > y_blue_low && b < y_blue_high);
}

bool ColorSensor::is_orange(int r, int g, int b)
{
    return (r > o_red_low && r < o_red_high) && 
            (g > o_green_low && g < o_green_high) && 
            (b > o_blue_low && b < o_blue_high);
}

void ColorSensor::sense()
{
    turn_red();
    delay(delayTime);
    rgb_arr[0] = analogRead(analogPin);

    turn_green();
    delay(delayTime);
    rgb_arr[1] = analogRead(analogPin);

    turn_blue();
    delay(delayTime);
    rgb_arr[2] = analogRead(analogPin);
    turn_off();
}

void ColorSensor::turn_red()
{
    digitalWrite(green_pin, LOW);
    digitalWrite(blue_pin, LOW);
    digitalWrite(red_pin, HIGH);
}

void ColorSensor::turn_blue()
{
    digitalWrite(red_pin, LOW);
    digitalWrite(green_pin, LOW);
    digitalWrite(blue_pin, HIGH);
}
void ColorSensor::turn_green()
{
    digitalWrite(blue_pin, LOW);
    digitalWrite(red_pin, LOW);
    digitalWrite(green_pin, HIGH);
}

void ColorSensor::turn_off()
{
    digitalWrite(red_pin, LOW);
    digitalWrite(green_pin, LOW);
    digitalWrite(blue_pin, LOW);
}

String ColorSensor::color_to_string(COLORS color){
    switch (color)
    {
    case RED:
        return "red";
        break;
    case GREEN:
        return "green";
        break;
    case BLUE:
        return "blue";
        break;
    case YELLOW:
        return "yellow";
        break;
    case BROWN:
        return "brown";
        break;
    case ORANGE:
        return "orange";
        break;
    case NOT_A_COLOR:
        return "NAC";
        break;
    default:
        break;
    }
}

void ColorSensor::calibrate()
{

    int vals[3];

    for (int i = 0; i <= 50; i++)
    {

        // set LED color to blue
        turn_blue();
        delay(delayTime); // wait for photo tranistor to come to steady state

        vals[0] = analogRead(analogPin); // read phototransistor and store value
        Serial.print(vals[0]);
        Serial.print("\t"); // print stored value.

        // set LED color to green
        turn_green();
        delay(delayTime); // wait for photo tranistor to come to steady state

        vals[1] = analogRead(analogPin); // read phototransistor and store value
        Serial.print(vals[1]);
        Serial.print("\t"); // print stored value.

        // set LED color to Red
        turn_red();
        delay(delayTime); // wait for photo tranistor to come to steady state

        vals[2] = analogRead(analogPin); // read phototransistor and store value
        Serial.println(vals[2]);         // print stored value.

        // turn off LED and wait for another cycle
        turn_off();
    }
    
}