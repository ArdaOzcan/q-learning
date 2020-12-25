#include "qlearning.hpp"

#include "utils.hpp"

QLearning::QLearning(std::string mapPath)
{
    Map map = Map(mapPath);
    Agent agent = Agent();
    grid = Grid(map, &agent);
    table = Table();

    epsilon = START_EPSILON;

    epsilonDecayValue = epsilon / (END_EPSILON_DECAYING - START_EPSILON_DECAYING);
}

Table *QLearning::getTable()
{
    return &table;
}

void QLearning::serializeTable(std::string fileName)
{
    table.serialize(fileName);
}

void QLearning::applyEpisode(bool log, bool render)
{
    if (render)
    {
        sf::RenderWindow win(sf::VideoMode(400, 400), "Q Learning");
        win.setFramerateLimit(20);
        applyEpisode(&win, log, render);
    }
    else
    {
        applyEpisode(nullptr, log, render);
    }
}

void QLearning::applyEpisode(sf::RenderWindow *win, bool log, bool render)
{
    grid.reset();
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
            if (log)
                std::cout << "Chose randomly; ";
            action = (Direction)(rand() % ACTION_AMOUNT);
        }
        else
        {
            if (log)
                std::cout << "Chose highest: " << table.getOptimalQValue(state) << "; ";
            action = (Direction)table.getOptimalQValueIndex(state);
        }

        grid.applyAction(action);
        if (log)
            std::cout << "Action: " << directionToString(action) << std::endl;
        sf::Vector2i newState = grid.getAgentPos();

        float reward = -5 + 20 / getDifference(newState, target);
        episodeEnded = grid.isObstacle(newState);
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
            // if (counter > EPISODES - 100)
            std::cout << "Got the reward at " << counter << std::endl;
            table.setQValue(state, action, 500);
            continue;
        }

        // https://en.wikipedia.org/wiki/Q-learning#Algorithm
        float optimalNewQ = table.getOptimalQValue(newState);
        float oldQ = table.getQValue(state, action);
        float updatedQValue = (1 - LEARNING_RATE) * oldQ + LEARNING_RATE * (reward + DISCOUNT * (optimalNewQ));

        table.setQValue(state, action, updatedQValue);

        if (render)
        {
            if (!win->isOpen())
                break;
            sf::Event e;
            while (win->pollEvent(e))
            {
                if (e.type == sf::Event::Closed)
                {
                    win->close();
                }
            }
            win->clear();
            grid.draw(win);
            // win->draw(sf::RectangleShape(sf::Vector2f(50, 50)));
            win->display();
        }
    }

    if (END_EPSILON_DECAYING >= counter && counter >= START_EPSILON_DECAYING)
    {
        epsilon -= epsilonDecayValue;
        if (log)
        {
            std::cout << "Epsilon changed, new epsilon: " << epsilon << std::endl;
            std::cout << epsilonDecayValue << std::endl;
        }
    }

    counter++;
}