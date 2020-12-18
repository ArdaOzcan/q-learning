#define GRID_WIDTH 20
#define GRID_HEIGHT 20
#include <iostream>


struct Map
{
private:
    bool obstacles[GRID_WIDTH][GRID_HEIGHT];

public:
    Map();
    Map(bool obstacles[GRID_WIDTH][GRID_HEIGHT]);
    Map(std::string fileName);

    bool isObstacle(int x, int y);
    void serialize(std::string fileName);
    void deserialize(std::string fileName);
};
