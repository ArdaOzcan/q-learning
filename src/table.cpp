#include "table.hpp"
#include <iostream>
#include <fstream>

Table::Table()
{
    // for (size_t x = 0; x < GRID_WIDTH; x++)
    // {
    //     for (size_t y = 0; y < GRID_HEIGHT; y++)
    //     {
    //         for (size_t i = 0; i < ACTION_AMOUNT; i++)
    //         {
    //             qTable[x][y][i] = 0;
    //         }
    //     }
    // }
}

float *Table::getAllQValues(int x, int y)
{
    return qTable[x][y];
}

float *Table::getAllQValues(sf::Vector2i v)
{
    return getAllQValues(v.x, v.y);
}

float Table::getOptimalQValue(int x, int y)
{
    float *allQValues = getAllQValues(x, y);
    float max = allQValues[0];
    for (size_t i = 0; i < ACTION_AMOUNT; i++)
    {
        float q = allQValues[i];
        if (q > max)
            max = q;
    }

    return max;
}

float Table::getOptimalQValue(sf::Vector2i v)
{
    return getOptimalQValue(v.x, v.y);
}

int Table::getOptimalQValueIndex(int x, int y)
{
    float *allQValues = getAllQValues(x, y);
    int max = 0;
    for (size_t i = 0; i < ACTION_AMOUNT; i++)
    {
        float q = allQValues[i];
        if (q > allQValues[max])
            max = i;
    }

    return max;
}

void Table::serialize(std::string fileName)
{
    std::ofstream ofs(fileName);

    for (int x = 0; x < GRID_WIDTH; x++)
    {
        for (int y = 0; y < GRID_HEIGHT; y++)
        {
            for (int i = 0; i < ACTION_AMOUNT; i++)
            {
                ofs << qTable[x][y][i] << ",";
            }
            ofs << std::endl;
            
        }
    }

    ofs.close();
}

void Table::deserialize(std::string fileName)
{
    std::ifstream ifs(fileName);
    std::string line;
    int l = 0;
    while(getline(ifs, line))
    {
        std::string num = "";
        int numIndex = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if(line[i] != ',') num += line[i];
            else
            {
                float numFloat = std::stof(num);
                qTable[l / GRID_WIDTH][l % GRID_WIDTH][numIndex++] = numFloat;
                num = "";
            }
        }
        l++;
    }

    ifs.close();
}

int Table::getOptimalQValueIndex(sf::Vector2i v)
{
    return getOptimalQValueIndex(v.x, v.y);
}

float Table::getQValue(int x, int y, Direction action)
{
    return qTable[x][y][(int)action];
}

float Table::getQValue(int x, int y, int action)
{
    return qTable[x][y][action];
}

float Table::getQValue(sf::Vector2i v, Direction action)
{
    return getQValue(v.x, v.y, action);
}

float Table::getQValue(sf::Vector2i v, int action)
{
    return getQValue(v.x, v.y, action);
}

void Table::setQValue(sf::Vector2i v, Direction direction, float val)
{
    qTable[v.x][v.y][(int)direction] = val;
}
