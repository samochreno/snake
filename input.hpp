#pragma once

namespace snake
{
    class Input
    {
    public:
        static auto init() -> void;

        static auto poll()  -> void;
        static auto clear() -> void;

        static auto left () -> bool;
        static auto right() -> bool;
    };
}