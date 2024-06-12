#line 1 "/Users/samochreno/repos/snake/indicator.hpp"
namespace snake
{
    class Indicator
    {
    public:
        static auto init() -> void;

        static auto set(bool value) -> void;
    };
}