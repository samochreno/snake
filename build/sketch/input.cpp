#line 1 "/Users/samochreno/repos/snake/input.cpp"
#include "input.hpp"

#include <Arduino.h>

namespace snake
{
    static bool wasLeftDown  = false;
    static bool wasRightDown = false;

    static bool isLeftDown  = false;
    static bool isRightDown = false;

    auto Input::init() -> void
    {
        pinMode(11, INPUT);
        pinMode(12, INPUT);
    }

    auto Input::poll() -> void
    {
        const bool left = digitalRead(11) == HIGH;
        if (left && !wasLeftDown) {
            isLeftDown = true;
        }
        wasLeftDown = left;

        const bool right = digitalRead(12) == HIGH;
        if (right && !wasRightDown) {
            isRightDown = true;
        }
        wasRightDown = right;
    }

    auto Input::clear() -> void
    {
        isLeftDown  = false;
        isRightDown = false;

    }

    auto Input::left() -> bool
    {
        return isLeftDown;
    }

    auto Input::right() -> bool
    {
        return isRightDown;
    }
}