#include "ColorSensor.hpp"

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
    return (r > 805 && r < 852) && (g > 894 && g < 960) && (b > 930 && b < 973);
}

bool ColorSensor::is_blue(int r, int g, int b)
{
    return (r > 863 && r < 995) && (g > 769 && g < 854) && (b > 798 && b < 835);
}

bool ColorSensor::is_green(int r, int g, int b)
{
    return (r > 849 && r < 944) && (g > 678 && g < 752) && (b > 889 && b < 941);
}

bool ColorSensor::is_brown(int r, int g, int b)
{
    return (r > 915 && r < 947) && (g > 888 && g < 947) && (b > 925 && b < 970);
}

bool ColorSensor::is_yellow(int r, int g, int b)
{
    return (r > 708 && r < 772) && (g > 621 && g < 775) && (b > 920 && b < 969);
}

bool ColorSensor::is_orange(int r, int g, int b)
{
    return (r > 721 && r < 783) && (g > 877 && g < 942) && (b > 920 && b < 975);
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
    digitalWrite(red_pin, HIGH);
    digitalWrite(green_pin, LOW);
    digitalWrite(blue_pin, LOW);
}

void ColorSensor::turn_blue()
{
    digitalWrite(red_pin, LOW);
    digitalWrite(green_pin, LOW);
    digitalWrite(blue_pin, HIGH);
}
void ColorSensor::turn_green()
{
    digitalWrite(red_pin, LOW);
    digitalWrite(green_pin, HIGH);
    digitalWrite(blue_pin, LOW);
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

    for (int i = 0; i <= 399; i++)
    {

        // set LED color to blue
        turn_blue();
        delay(delayTime); // wait for photo tranistor to come to steady state

        vals[0] = analogRead(analogPin); // read phototransistor and store value
        Serial.print(vals[0]);
        Serial.print(", "); // print stored value.

        // set LED color to green
        turn_green();
        delay(delayTime); // wait for photo tranistor to come to steady state

        vals[1] = analogRead(analogPin); // read phototransistor and store value
        Serial.print(vals[1]);
        Serial.print(", "); // print stored value.

        // set LED color to Red
        turn_red();
        delay(delayTime); // wait for photo tranistor to come to steady state

        vals[2] = analogRead(analogPin); // read phototransistor and store value
        Serial.println(vals[2]);         // print stored value.

        // turn off LED and wait for another cycle
        turn_off();
    }
    
}