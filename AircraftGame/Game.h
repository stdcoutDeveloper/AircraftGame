#pragma once

#include <SFML/Graphics.hpp>

namespace AircraftGame
{
    class Game
    {
    public:
        Game() : window_(sf::VideoMode(640, 480), "SFML Application"), player_()
        {
            player_.setRadius(40.0f);
            player_.setPosition(100.0f, 100.0f);
            player_.setFillColor(sf::Color::Cyan);
        }

        void Run()
        {
            while (window_.isOpen())
            {
                ProcessEvents();
                Update();
                Render();
            }
        }

    private:
        sf::RenderWindow window_;
        sf::CircleShape player_;

        /**
         * \brief Handles user input
         */
        void ProcessEvents()
        {
            sf::Event event;
            while (window_.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window_.close();
            }
        }

        /**
         * \brief Updates the game logic ( everything that happens in the game)
         */
        void Update()
        {
        }

        /**
         * \brief Renders the game to the screen
         * First, clear the window with a color, usually black
         * Then, draw all the objects of the current frame 
         * After drawn everything, display it on the screen
         */
        void Render()
        {
            window_.clear();
            window_.draw(player_);
            window_.display();
        }
    };
}
