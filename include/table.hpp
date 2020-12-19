#pragma once

#include "grid.hpp"

class Table
{
private:
    float qTable[GRID_WIDTH][GRID_HEIGHT][ACTION_AMOUNT];

public:
    Table();
    float *getAllQValues(int x, int y);
    float *getAllQValues(sf::Vector2i v);

    float getOptimalQValue(int x, int y);
    float getOptimalQValue(sf::Vector2i v);

    int getOptimalQValueIndex(int x, int y);
    int getOptimalQValueIndex(sf::Vector2i v);

    float getQValue(int x, int y, Direction action);
    float getQValue(int x, int y, int action);
    float getQValue(sf::Vector2i v, Direction action);
    float getQValue(sf::Vector2i v, int action);

    void setQValue(sf::Vector2i, Direction action, float val);
};
