#include "LCD.hpp"


LCD::LCD(int width, int height) {
    this->width = width;
    this->height = height;

    lcd = new LiquidCrystal_I2C(0x27, width, height);
    lcd->init();
    lcd->backlight();
}

LCD::~LCD() {
    delete lcd;
}

void LCD::show_number() {
    
}

void LCD::test(){
    lcd->setCursor(0,1); 

    lcd->print("There,          "); 



    for (int i = 0; i < 16; i++) 

    { 

        lcd->setCursor(i, 0); 

        lcd->print(" >"); 

        delay(250); 

    } 



    lcd->setCursor(0,1); 

    lcd->print("and Back Again! "); 



    for (int i = 15; i >= 0; i--) 

    { 

        lcd->setCursor(i, 0); 

        lcd->print("< "); 

        delay(250); 

    } 

}