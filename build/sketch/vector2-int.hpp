#line 1 "/Users/samochreno/repos/snake/vector2-int.hpp"
#pragma once

namespace snake
{
    struct Vector2Int
    {
        Vector2Int() = default;
        Vector2Int(int8_t x, int8_t y)
            : x{ x }, y{ y }
        {
        }

        auto operator==(const Vector2Int& other) const -> bool
        {
            return x == other.x && y == other.y;
        }

        int8_t x{};
        int8_t y{};
    };
}