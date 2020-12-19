#include <SFML/Graphics.hpp>
#include <iostream>

#include "table.hpp"

std::string vectorToString(sf::Vector2i v)
{
    std::string ret = "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
    return ret;
}

std::string directionToString(Direction drc)
{
    switch (drc)
    {
    case up:
        return "up";
    case right:
        return "right";
    case down:
        return "down";
    case left:
        return "left";
    default:
        return "unknown";
    }
}

int main()
{
    // sf::RenderWindow window(sf::VideoMode(200, 200), "Q Learning");
    // window.setFramerateLimit(1);

    Map map = Map("data/test.map");
    Agent agent = Agent();
    Grid grid = Grid(map, &agent);
    Table table = Table();

    bool log = false;
    
    float epsilon = 0.5;

    int START_EPSILON_DECAYING = 1;
    int END_EPSILON_DECAYING = EPISODES / 2;
    
    float epsilonDecayValue = epsilon/(END_EPSILON_DECAYING-START_EPSILON_DECAYING);

    for (size_t i = 0; i < EPISODES; i++)
    {
        log = (i == EPISODES - 1);
        if (log)
            std::cout << "Episode: " << i << std::endl;
        agent.resetPos();
        bool episodeEnded = false;
        while (!episodeEnded)
        {
            sf::Vector2i state = grid.getAgentPos();
            if (log)
                std::cout << vectorToString(state) << std::endl;
            float p = (rand() % 100) / 100.0;
            Direction action;
            if (p < epsilon)
            {
                if(log) std::cout << "Chose randomly; ";
                action = (Direction)(rand() % ACTION_AMOUNT);
            }
            else
            {
                if(log) std::cout << "Chose highest: " << table.getOptimalQValue(state) << "; ";
                action = (Direction)table.getOptimalQValueIndex(state);
            }

            agent.go(action);
            if (log)
                std::cout << "Action: " << directionToString(action) << std::endl;
            sf::Vector2i newState = grid.getAgentPos();

            float reward = -5;
            episodeEnded = map.isObstacle(newState);
            if (episodeEnded)
            {
                if (log)
                    std::cout << "Tossed to an obstacle " << vectorToString(newState) << std::endl;
                table.setQValue(state, action, -50);
                continue;
            }

            if (newState == sf::Vector2i(GRID_WIDTH - 1, GRID_HEIGHT - 1))
            {
                table.setQValue(state, action, 50);
                episodeEnded = true;
                std::cout << "Got the reward at " << i << std::endl;
                continue;
            }

            // https://en.wikipedia.org/wiki/Q-learning#Algorithm
            float optimalNewQ = table.getOptimalQValue(newState);
            float oldQ = table.getQValue(state, action);
            float updatedQValue = (1 - LEARNING_RATE) * oldQ + LEARNING_RATE * (reward + DISCOUNT * (optimalNewQ));

            table.setQValue(state, action, updatedQValue);
        }

        if(END_EPSILON_DECAYING >= i && i >= START_EPSILON_DECAYING)
        {
            epsilon -= epsilonDecayValue;
        }

        // if (log)
        // {
        //     for (size_t x = 0; x < GRID_WIDTH; x++)
        //     {
        //         for (size_t y = 0; y < GRID_WIDTH; y++)
        //         {
        //             for (size_t i = 0; i < ACTION_AMOUNT; i++)
        //             {
        //                 std::cout << table.getQValue(x, y, i) << ", ";
        //             }
        //             std::cout << "||";
        //         }

        //         std::cout << std::endl;
        //     }
        // }
    }

    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     Direction action = (Direction)(rand() % 4);
    //     agent.go(action);

    //     sf::Vector2i agentPos = grid.getAgentPos();
    //     std::cout << "State: " << vectorToString(agentPos) << "; Obstacle: " << map.isObstacle(agentPos) << std::endl;

    //     window.clear();
    //     grid.draw(window);
    //     window.display();
    // }

    return 0;
}