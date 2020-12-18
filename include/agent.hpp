#include <SFML/Graphics.hpp>

enum Direction
{
    up,
    right,
    down,
    left
};

class Agent
{
private:
    sf::Vector2i pos;
    sf::Color color;

public:
    Agent(sf::Color color = sf::Color::Green);

    sf::Vector2i getPos();
    sf::Color getColor();

    void go(Direction drc);
};
