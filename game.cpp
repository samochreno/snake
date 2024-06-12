#include "game.hpp"

#include <Arduino.h>
#include <ArrayList.h>

#include "input.hpp"
#include "lcd.hpp"
#include "indicator.hpp"
#include "vector2-int.hpp"

namespace snake
{
    enum class Direction
    {
        Up,
        Down,
        Left,
        Right,
    };

    static auto get_next(Direction direction) -> Direction
    {
        switch (direction) {
        case Direction::Up:
            return Direction::Right;
        case Direction::Right:
            return Direction::Down;
        case Direction::Down:
            return Direction::Left;
        case Direction::Left:
            return Direction::Up;
        }
    }

    static auto get_previous(Direction direction) -> Direction {
        switch (direction) {
        case Direction::Up:
            return Direction::Left;
        case Direction::Left:
            return Direction::Down;
        case Direction::Down:
            return Direction::Right;
        case Direction::Right:
            return Direction::Up;
        }
    }

    static auto get_vector2_int(Direction direction) -> Vector2Int
    {
        switch (direction) {
        case Direction::Up:
            return Vector2Int{  0, -1 };
        case Direction::Down:
            return Vector2Int{  0,  1 };
        case Direction::Left:
            return Vector2Int{ -1,  0 };
        case Direction::Right:
            return Vector2Int{  1,  0 };
        }
    }

    bool is_running{};
    unsigned long last_step_time = millis();
    const unsigned long STEP_DURATION = 500;

    ArrayList<Vector2Int> body{};
    Direction direction{};
    Vector2Int previous_last_segment{};
    Vector2Int food{};
    uint8_t score{};

    auto Game::init() -> void
    {
        Input::init();
        Lcd::init();
        Indicator::init();

        run();
    }

    auto Game::tick() -> void
    {
        Input::poll();

        const auto currentTime = millis();
        auto deltaTime = currentTime - last_step_time;

        while (deltaTime > STEP_DURATION) {
            step();
            Input::clear();
            deltaTime -= STEP_DURATION;
            last_step_time = currentTime;
        }
    }

    auto Game::step() -> void
    {
        Indicator::set(!is_running);

        if (!is_running) {
            if (Input::left() || Input::right()) {
                run();
            }

            return;
        }

        if (Input::left()) {
            direction = get_previous(direction);
        }

        if (Input::right()) {
            direction = get_next(direction);
        }

        previous_last_segment = body.get(body.size() - 1);

        for (int8_t i = (body.size() - 1); i > 0; --i) {
            body.set(i, body.get(i - 1));
        }

        const auto direction = get_vector2_int(snake::direction);
        body.set(0, Vector2Int {
            body.get(0).x + direction.x,
            body.get(0).y + direction.y,
        });

        if (is_dead()) {
            die();
            return;
        }

        if (is_on_food()) {
            eat_food();
        }

        render();
    }

    auto Game::render() -> void
    {
        Lcd::get_instance().clear();

        for (const auto& segment : body) {
            Lcd::get_instance().setCursor(segment.x, segment.y);
            Lcd::get_instance().print("#");
        }

        Lcd::get_instance().setCursor(food.x, food.y);
        Lcd::get_instance().print("O");
    }

    auto Game::run() -> void
    {
        is_running = true;

        last_step_time = millis();

        direction = Direction::Right;
        body.clear();
        body.add(Vector2Int {
            Lcd::COLUMNS / 2 - 1,
            Lcd::ROWS    / 2 - 1,
        });

        score = 0;
        spawn_food();
    }

    auto Game::grow() -> void
    {
        body.add(previous_last_segment);
    }

    auto Game::is_dead() -> bool
    {
        const auto position = body.get(0);

        if (position.x < 0) {
            return true;
        }

        if (position.y < 0) {
            return true;
        }

        if (position.x >= Lcd::COLUMNS) {
            return true;   
        }

        if (position.y >= Lcd::ROWS) {
            return true;
        }

        for (int8_t i = 1; i < body.size(); ++i) {
            if (position == body.get(i)) {
                return true;
            }
        }

        return false;
    }

    auto Game::die() -> void
    {
        is_running = false;
        Indicator::set(true);
        Lcd::get_instance().clear();

        Lcd::get_instance().setCursor(5, 0);
        Lcd::get_instance().print("Zomrel si!");

        Lcd::get_instance().setCursor(6, 1);
        Lcd::get_instance().print("Skore: ");
        Lcd::get_instance().print(score);

        Lcd::get_instance().setCursor(2, 3);
        Lcd::get_instance().print("Stlac pre reset");
    }

    static auto generate_food_position() -> Vector2Int
    {
        return {
            random() % Lcd::COLUMNS,
            random() % Lcd::ROWS,
        };
    }

    auto Game::spawn_food() -> void
    {
        food = generate_food_position();
        while (body.contains(food)) {
            food = generate_food_position();
        }
    }

    auto Game::is_on_food() -> bool
    {
        return body.get(0) == food;
    }

    auto Game::eat_food() -> void
    {
        score++;
        grow();
        spawn_food();
    }
}