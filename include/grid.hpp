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
    Grid();

    void draw(sf::RenderWindow &win);
    void reset();
    void applyAction(Direction drc);
    
    sf::Vector2i getAgentPos();
    bool isObstacle(sf::Vector2i v);
};
