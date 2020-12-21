#include "utils.hpp"


#include <iostream>
#include <math.h>

std::string vectorToString(sf::Vector2i v)
{
    std::string ret = "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
    return ret;
}

float getDifference(sf::Vector2i v1, sf::Vector2i v2)
{
    return std::sqrt(std::pow(std::abs(v1.x - v2.x), 2) + std::pow(std::abs(v1.y - v2.y), 2));
}

std::string directionToString(Direction drc)
{
    switch (drc)
    {
    case up:
        return "up";
    case right:
        return "right";
    case down:
        return "down";
    case left:
        return "left";
    default:
        return "unknown";
    }
}