#include "table.hpp"
#include "grid.hpp"

class QLearning
{
private:
    Table table;
    Grid grid;
    
    float epsilon;
    
    int START_EPSILON_DECAYING = 1;
    int END_EPSILON_DECAYING = EPISODES;

    float epsilonDecayValue;

    sf::Vector2i target = sf::Vector2i(GRID_WIDTH - 1, GRID_HEIGHT - 1);

    int counter = 0;

public:
    QLearning(std::string mapPath);

    Table * getTable();
    void applyEpisode(bool log = false, bool render = false);
    void applyEpisode(sf::RenderWindow *win, bool log = false, bool render = false);
    void serializeTable(std::string tableName);
};