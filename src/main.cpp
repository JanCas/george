#include <Arduino.h>

#include "MotorEncoder.hpp"
#include "ColorSensor.hpp"
#include "LCD.hpp"

bool running = false;
char serial_byte;

MotorEncoder motor_encoder(12, 11, 10, 20, 21, 380, 12);
ColorSensor color_sensor(5, 6, 7, A0);
LCD lcd(16, 2);
// LiquidCrystal_I2C lcd(0x3f, 16, 2);

double pos_des = 72.5;

void display_color(COLORS color){
    lcd.clear_row(1);
    switch (color)
    {
    case RED:
        lcd.display_message("RED", CENTER, 1);
        break;
    case GREEN:
        lcd.display_message("GREEN", CENTER, 1);
        break;
    case BLUE:
        lcd.display_message("BLUE", CENTER, 1);
        break;
    case YELLOW:
        lcd.display_message("YELLOW", CENTER, 1);
        break;
    case BROWN:
        lcd.display_message("BROWN", CENTER, 1);
        break;
    case ORANGE:
        lcd.display_message("ORANGE", CENTER, 1);
        break;
    case NOT_A_COLOR:
        lcd.display_message("NOT A COLOR", CENTER, 1);
    default:
        break;
    }
}

void setup()
{
    Serial.begin(9600);
    // Serial.println(color_sensor.get_color());
    lcd.init();
    lcd.display_message("color: ", CENTER, 0);
}

void loop()
{
    if (Serial.available() > 0){
        serial_byte = Serial.read();
    }

    if (serial_byte == 'g'){
        serial_byte = '0';
        color_sensor.calibrate();
        Serial.println("-----------------------");
        Serial.println();
   }

   if (serial_byte == 's'){
       serial_byte = '0';
       display_color(color_sensor.get_color());
   }
}