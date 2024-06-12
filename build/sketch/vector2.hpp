#line 1 "/Users/samochreno/repos/snake/vector2.hpp"
#pragma once

namespace snake
{
    struct Vector2
    {
        Vector2() = default;
        Vector2(float x, float y)
            : x{ x }, y{ y }
        {
        }

        auto operator==(const Vector2& other) const -> bool
        {
            return x == other.x && y == other.y;
        }


        float x{};
        float y{};
    };
}