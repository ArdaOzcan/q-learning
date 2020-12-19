#pragma once
#include "map.hpp"


struct Grid
{
private:
    sf::RectangleShape tiles[GRID_WIDTH][GRID_HEIGHT];
    Map map;
    Agent *agent;

public:
    Grid(Map map, Agent *agent);
    void draw(sf::RenderWindow &win);
    sf::Vector2i getAgentPos();
};
