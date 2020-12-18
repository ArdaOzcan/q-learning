#include <SFML/Graphics.hpp>
#include "grid.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Q Learning");

    Map map = Map("data/test.map");
    Agent agent = Agent();
    Grid grid = Grid(map, &agent);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    agent.go(Direction::up);
                    break;
                case sf::Keyboard::D:
                    agent.go(Direction::right);
                    break;
                case sf::Keyboard::S:
                    agent.go(Direction::down);
                    break;
                case sf::Keyboard::A:
                    agent.go(Direction::left);
                    break;
                }
            }
        }

        window.clear();
        grid.draw(window);
        window.display();
    }

    return 0;
}