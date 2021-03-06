#include "grid.hpp"

Grid::Grid(Map map, Agent *agent)
{
    this->agent = agent;
    this->map = map;
    for (size_t x = 0; x < GRID_WIDTH; x++)
    {
        for (size_t y = 0; y < GRID_HEIGHT; y++)
        {
            sf::RectangleShape tile(sf::Vector2f(10, 10));
            tile.setPosition(sf::Vector2f(10 * x, 10 * y));
            sf::Color tileColor = this->map.isObstacle(x, y) ? sf::Color(255, 0, 0) : sf::Color(255, 255, 255);

            tile.setFillColor(tileColor);
            tiles[x][y] = tile;
        }
    }
}

Grid::Grid() {}

void Grid::reset()
{
    agent->resetPos();
}

void Grid::applyAction(Direction drc)
{
    agent->go(drc);
}

void Grid::draw(sf::RenderWindow *win)
{
    for (size_t x = 0; x < GRID_WIDTH; x++)
    {
        for (size_t y = 0; y < GRID_HEIGHT; y++)
        {
            if (agent->getPos() == sf::Vector2i(x, y))
            {
                sf::RectangleShape rect(sf::Vector2f(10, 10));
                rect.setPosition(x * 10, y * 10);
                rect.setFillColor(agent->getColor());
                win->draw(rect);
            }
            else
            {
                win->draw(tiles[x][y]);
            }
        }
    }
}

bool Grid::isObstacle(sf::Vector2i v)
{
    return map.isObstacle(v);
}

sf::Vector2i Grid::getAgentPos()
{
    return agent->getPos();
}