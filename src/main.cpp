#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "table.hpp"

std::string vectorToString(sf::Vector2i v)
{
    std::string ret = "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
    return ret;
}

float getDifference(sf::Vector2i v1, sf::Vector2i v2)
{
    return std::sqrt(std::pow(std::abs(v1.x - v2.x), 2) + std::pow(std::abs(v1.y - v2.y), 2));
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

void render(Table &table, Agent &agent, Grid &grid, float epsilon)
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Q Learning");
    window.setFramerateLimit(15);

    agent.resetPos();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i state = grid.getAgentPos();

        float p = (rand() % 100) / 100.0;
        Direction action;
        if (p < epsilon)
        {
            std::cout << "Chose randomly; ";
            action = (Direction)(rand() % ACTION_AMOUNT);
        }
        else
        {
            std::cout << "Chose highest: " << table.getOptimalQValue(state) << "; ";
            action = (Direction)table.getOptimalQValueIndex(state);
        }

        agent.go(action);
        std::cout << "Action: " << directionToString(action) << std::endl;
        sf::Vector2i newState = grid.getAgentPos();

        if (grid.isObstacle(newState))
        {
            std::cout << "Tossed to an obstacle " << vectorToString(newState) << std::endl;
            window.close();
        }

        if (newState == sf::Vector2i(GRID_WIDTH - 1, GRID_HEIGHT - 1))
        {
            std::cout << "Got the reward" << std::endl;
            window.close();
        }

        window.clear();
        grid.draw(window);
        window.display();
    }
}

int main()
{
    Map map = Map("data/test.map");
    Agent agent = Agent();
    Grid grid = Grid(map, &agent);
    Table table = Table();

    bool log = false;

    float epsilon = START_EPSILON;

    int START_EPSILON_DECAYING = 1;
    int END_EPSILON_DECAYING = EPISODES / 2;

    float epsilonDecayValue = epsilon / (END_EPSILON_DECAYING - START_EPSILON_DECAYING);
    sf::RenderWindow window;


    sf::Vector2i target = sf::Vector2i(GRID_WIDTH - 1, GRID_HEIGHT - 1);

    for (size_t i = 0; i < EPISODES; i++)
    {
        // log = (i == EPISODES - 1);
        // log = (i % 900000 == 0);
        

        // if(i % 18000000 == 0) 
        // {
        //     render(table, agent, grid, epsilon);
        // }

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
                if (log) std::cout << "Chose randomly; ";
                action = (Direction)(rand() % ACTION_AMOUNT);
            }
            else
            {
                if (log) std::cout << "Chose highest: " << table.getOptimalQValue(state) << "; ";
                action = (Direction)table.getOptimalQValueIndex(state);
            }

            agent.go(action);
            if (log)
                std::cout << "Action: " << directionToString(action) << std::endl;
            sf::Vector2i newState = grid.getAgentPos();

            float reward = -5 + 20/getDifference(newState, target);
            episodeEnded = map.isObstacle(newState);
            if (episodeEnded)
            {
                if (log)
                    std::cout << "Tossed to an obstacle " << vectorToString(newState) << std::endl;
                table.setQValue(state, action, -100);
                continue;
            }

            if (newState == target)
            {
                episodeEnded = true;
                if(i > EPISODES - 2500)
                    std::cout << "Got the reward at " << i << std::endl;
                table.setQValue(state, action, 500);
                continue;
            }

            // https://en.wikipedia.org/wiki/Q-learning#Algorithm
            float optimalNewQ = table.getOptimalQValue(newState);
            float oldQ = table.getQValue(state, action);
            float updatedQValue = (1 - LEARNING_RATE) * oldQ + LEARNING_RATE * (reward + DISCOUNT * (optimalNewQ));

            table.setQValue(state, action, updatedQValue);
        }

        if (END_EPSILON_DECAYING >= i && i >= START_EPSILON_DECAYING)
        {
            epsilon -= epsilonDecayValue;
            if (log)
            {
                std::cout << "Epsilon changed, new epsilon: " << epsilon << std::endl;
                std::cout << epsilonDecayValue << std::endl;
            }
        }

        // render(table, agent, grid, epsilon);
    }

    render(table, agent, grid, epsilon);

    return 0;
}