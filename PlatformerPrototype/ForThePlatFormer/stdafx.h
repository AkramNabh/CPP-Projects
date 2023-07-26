

// an include to run the libraries as precompiled in the background, to cut down running time


#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <ctime>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <map>
#include <string>


/*
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    // Create a map of textures
    std::map<std::string, sf::Texture> textures;
    if (!textures["texture1"].loadFromFile("texture1.png"))
    {
        std::cout << "Failed to load texture1\n";
        return -1;
    }
    if (!textures["texture2"].loadFromFile("texture2.png"))
    {
        std::cout << "Failed to load texture2\n";
        return -1;
    }

    // Create a vector of sprites
    std::vector<sf::Sprite> sprites;
    sprites.push_back(sf::Sprite(textures["texture1"]));
    sprites[0].setPosition(100, 100);
    sprites.push_back(sf::Sprite(textures["texture2"]));
    sprites[1].setPosition(200, 200);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        // Draw each sprite
        for (const auto& sprite : sprites)
        {
            window.draw(sprite);
        }

        window.display();
    }

    return 0;
}
*/