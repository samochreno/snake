#include <Arduino.h>

#include "input.hpp"
#include "lcd.hpp"
#include "game.hpp"

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