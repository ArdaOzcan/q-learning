#include "agent.hpp"

Agent::Agent(sf::Color color)
{
    this->color = color;
}

sf::Vector2i Agent::getPos()
{
    return pos;
}

sf::Color Agent::getColor()
{
    return color;
}

void Agent::go(Direction drc)
{
    switch (drc)
    {
    case Direction::up:
        pos.y -= 1;
        break;
    case Direction::right:
        pos.x += 1;
        break;
    case Direction::down:
        pos.y += 1;
        break;
    case Direction::left:
        pos.x -= 1;
        break;
    }
}