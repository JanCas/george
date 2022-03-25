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
    return (r > 698 && r < 785) && (g > 818 && g < 926) && (b > 870 && b < 934);
}

bool ColorSensor::is_blue(int r, int g, int b)
{
    return (r > 842 && r < 994) && (g > 553 && g < 972) && (b > 620 && b < 879);
}

bool ColorSensor::is_green(int r, int g, int b)
{
    return (r > 816 && r < 883) && (g > 487 && g < 696) && (b > 806 && b < 907);
}

bool ColorSensor::is_brown(int r, int g, int b)
{
    return (r > 852 && r < 931) && (g > 843 && g < 916) && (b > 870 && b < 953);
}

bool ColorSensor::is_yellow(int r, int g, int b)
{
    return (r > 515 && r < 672) && (g > 468 && g < 700) && (b > 822 && b < 936);
}

bool ColorSensor::is_orange(int r, int g, int b)
{
    return (r > 581 && r < 690) && (g > 842 && g < 898) && (b > 859 && b < 919);
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