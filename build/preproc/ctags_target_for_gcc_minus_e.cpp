# 1 "/Users/samochreno/repos/snake/snake.ino"
# 2 "/Users/samochreno/repos/snake/snake.ino" 2

# 4 "/Users/samochreno/repos/snake/snake.ino" 2
# 5 "/Users/samochreno/repos/snake/snake.ino" 2
# 6 "/Users/samochreno/repos/snake/snake.ino" 2

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
