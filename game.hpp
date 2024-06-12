#pragma once

namespace snake
{
    class Game
    {
    public:
        static auto init() -> void;
        static auto tick() -> void;

    private:
        static auto step() -> void;
        static auto render() -> void;

        static auto run() -> void;

        static auto grow() -> void;

        static auto is_dead() -> bool;
        static auto die() -> void;

        static auto spawn_food() -> void;
        static auto is_on_food() -> bool;
        static auto eat_food() -> void;
   };
}