#pragma once

#include <LiquidCrystal_I2C.h>

namespace snake
{
    class Lcd
    {
    public:
        static auto init() -> void;
        static auto get_instance() -> LiquidCrystal_I2C&;

        static inline int8_t ROWS    = 4;
        static inline int8_t COLUMNS = 20;
    };
}