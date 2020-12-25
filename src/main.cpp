#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "table.hpp"
#include "utils.hpp"

#include "qlearning.hpp"

int main()
{
    QLearning qLearning = QLearning("data/test.map");

    for (size_t i = 0; i < EPISODES; i++)
    {
        qLearning.applyEpisode(false, i == EPISODES - 1);
    }

    qLearning.serializeTable("test.table");

    return 0;
}