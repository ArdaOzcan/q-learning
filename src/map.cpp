#include "map.hpp"
#include <iostream>
#include <fstream>

Map::Map()
{
}

Map::Map(bool obstacles[GRID_WIDTH][GRID_HEIGHT])
{
    for (int x = 0; x < GRID_WIDTH; x++)
    {
        for (int y = 0; y < GRID_HEIGHT; y++)
        {
            this->obstacles[x][y] = obstacles[x][y];
        }
    }
}

Map::Map(std::string fileName)
{
    deserialize(fileName);
}

bool Map::isObstacle(int x, int y)
{
    if(x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)
        return true;
        
    return obstacles[x][y];
}


bool Map::isObstacle(sf::Vector2i v)
{
    return isObstacle(v.x, v.y);
}


void Map::serialize(std::string fileName)
{
    std::ofstream ofs(fileName);

    for (size_t x = 0; x < GRID_WIDTH; x++)
    {
        for (size_t y = 0; y < GRID_HEIGHT; y++)
        {
            ofs << obstacles[x][y];
        }

        ofs << std::endl;
    }

    ofs.close();
}

void Map::deserialize(std::string fileName)
{
    std::ifstream ifs(fileName);
    for (size_t y = 0; y < GRID_HEIGHT; y++)
    {
        std::string line;
        ifs >> line;

        for (int i = 0; i < line.length(); i++)
        {
            obstacles[y][i] = (line[i] != '0');
        }
    }

    ifs.close();
}