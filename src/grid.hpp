#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "agent.hpp"

struct Grid
{
private:
    sf::RectangleShape tiles[GRID_WIDTH][GRID_HEIGHT];
    Map map;
    Agent *agent;

public:
    Grid(Map map, Agent *agent);
    void draw(sf::RenderWindow &win);
};
