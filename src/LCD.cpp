#include "LCD.hpp"


LCD::LCD(int width, int height) {
    this->width = width;
    this->height = height;

    lcd = new LiquidCrystal_I2C(0x27, width, height);
}

LCD::~LCD() {
    delete lcd;
}

void LCD::init(){
    lcd->init();
    lcd->backlight();
}

void LCD::display_message(String message, ALIGNMENT_ENUM alignment, int row) {

    switch(alignment){
        case LEFT:
            display_left_aligned(message, row);
            break;
        case RIGHT:
            display_right_aligned(message, row);
            break;
        case CENTER:
            display_center_aligned(message, row);
            break;
    }    
}

void LCD::display_left_aligned(String message, int row){
    lcd->setCursor(0, row);
    lcd->print(message);
}

void LCD::display_center_aligned(String message, int row){
    int cursor_set = (width / 2) - (message.length() / 2);
    
    lcd->setCursor(cursor_set, row);
    lcd->print(message);
}

void LCD::display_right_aligned(String message, int row){
    lcd->setCursor(width-message.length(), row);
    lcd->print(message);
}