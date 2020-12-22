#pragma once

#include <iostream>

#include "agent.hpp"

#include "definitions.hpp"


struct Map
{
private:
    bool obstacles[GRID_WIDTH][GRID_HEIGHT];

public:
    Map();
    Map(bool obstacles[GRID_WIDTH][GRID_HEIGHT]);
    Map(std::string fileName);

    bool isObstacle(int x, int y);
    bool isObstacle(sf::Vector2i pos);
    void serialize(std::string fileName);
    void deserialize(std::string fileName);
};
