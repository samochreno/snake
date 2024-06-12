#line 1 "/Users/samochreno/repos/snake/snake.ino"
#include <Arduino.h>

#include "input.hpp"
#include "lcd.hpp"
#include "game.hpp"

#line 7 "/Users/samochreno/repos/snake/snake.ino"
void setup();
#line 15 "/Users/samochreno/repos/snake/snake.ino"
void loop();
#line 7 "/Users/samochreno/repos/snake/snake.ino"
void setup()
{
	Serial.begin(9600);
	Serial.println("Serial begin successful!");	
	randomSeed(analogRead(0));
	snake::Game::init();
}

void loop()
{
	snake::Game::tick();
}
