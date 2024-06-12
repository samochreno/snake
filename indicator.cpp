#include "indicator.hpp"

#include <Arduino.h>

namespace snake
{
    auto Indicator::init() -> void
    {
        pinMode(2, OUTPUT);
    }

    auto Indicator::set(bool value) -> void
    {
        digitalWrite(2, value ? HIGH : LOW);
    }
}