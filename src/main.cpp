#include <Arduino.h>

#include "MotorEncoder.hpp"
#include "ColorSensor.hpp"
#include "LCD.hpp"
#include "Disk.hpp"
#include "Module.hpp"
#include "Swiveler.hpp"

bool running = false;
char serial_byte;

MotorEncoder motor_encoder(12, 11, 10, 2, 3, 380, 12);
ColorSensor color_sensor(5, 6, 7, A0);
LCD lcd(16, 2);
Disk disk(&motor_encoder);
cppQueue *mm_command_queue = new cppQueue(sizeof(mm_attr), 2, FIFO, true);
Swiveler swively(8);

COLORS assigned_color = BLUE;

double pos_des = 72.5;

void display_color(COLORS color)
{
    lcd.clear_row(1);
    switch (color)
    {
    case RED:
        lcd.display_message("RED", CENTER, 1);
        Serial.println("RED");
        break;
    case GREEN:
        lcd.display_message("GREEN", CENTER, 1);
        Serial.println("GREEN");
        break;
    case BLUE:
        lcd.display_message("BLUE", CENTER, 1);
        Serial.println("BLUE");
        break;
    case YELLOW:
        lcd.display_message("YELLOW", CENTER, 1);
        Serial.println("YELLOW");
        break;
    case BROWN:
        lcd.display_message("BROWN", CENTER, 1);
        Serial.println("BROWN");
        break;
    case ORANGE:
        lcd.display_message("ORANGE", CENTER, 1);
        Serial.println("ORANGE");
        break;
    case NOT_A_COLOR:
        lcd.display_message("NOT A COLOR", CENTER, 1);
        Serial.println("NOT A COLOR");
    default:
        break;
    }
}

void move_swiveler(const mm_attr &mm_at_swiveler)
{
    if (mm_at_swiveler.metal)
    {
        swively.move_to(CLOSED);
        return;
    }
    if (mm_at_swiveler.right_color)
    {
        swively.move_to(BUCKET);
    }
    else
    {
        swively.move_to(NEXT_MODULE);
    }
}

void check_mm()
{

    mm_attr *mm = new mm_attr;

    mm->metal = false;
    mm_command_queue->push(&mm);

    // there is an mm at the metal part
    if (mm_command_queue->getCount() > 1)
    {
        mm_attr *mm_at_color = nullptr;
        mm_command_queue->peek(&mm_at_color);

        COLORS mm_color = color_sensor.get_color();
        Serial.print("The color is: ");
        display_color(mm_color);

        if (mm_color == assigned_color)
        {
            mm_at_color->right_color = true;
        }
        else
        {
            mm_at_color->right_color = false;
        }
    }

    if (mm_command_queue->getCount() == 2)
    {
        mm_attr *return_mm = nullptr;

        if (mm_command_queue->pop(&return_mm))
        {
            move_swiveler(*return_mm);
        }

        delete return_mm;
    }
    Serial.println();
}

void setup()
{
    Serial.begin(9600);
    lcd.init();
    lcd.display_message("color: ", CENTER, 0);
    swively.init();
    motor_encoder.set_pid_values(1,0,0,.05);
}

void loop()
{
    if (disk.move_to_next())
    {
        check_mm();
        // delay(1000);
    }
}