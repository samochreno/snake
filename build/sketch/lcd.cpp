#line 1 "/Users/samochreno/repos/snake/lcd.cpp"
#include "lcd.hpp"

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); 

namespace snake
{
    void Lcd::init()
    {
        lcd.init();
        lcd.backlight();
    }

    auto Lcd::get_instance() -> LiquidCrystal_I2C&
    {
        return lcd;
    }
}