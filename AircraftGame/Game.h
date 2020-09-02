#pragma once

#include "World.h"
#include "Player.h"

namespace AircraftGame
{
    class Game
    {
    public:
        const float PLAYER_SPEED = 100.0f;
        const sf::Time TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);

        Game() : window_(sf::VideoMode(640, 480), "SFML Application", sf::Style::Close), world_(window_)
        {
        }

        void Run()
        {
            sf::Clock clock;
            sf::Time timeSinceLastUpdate = sf::Time::Zero;

            while (window_.isOpen())
            {
                ProcessInput();
                timeSinceLastUpdate += clock.restart();

                while (timeSinceLastUpdate > TIME_PER_FRAME)
                {
                    timeSinceLastUpdate -= TIME_PER_FRAME;

                    ProcessInput();
                    if (!isPaused_)
                        Update(TIME_PER_FRAME);
                }

                Render();
            }
        }

    private:
        sf::RenderWindow window_;
        World world_;
        Player player_;

        bool isMovingUp_ = false, isMovingDown_ = false, isMovingLeft_ = false, isMovingRight_ = false;
        bool isPaused_ = false;

        /**
         * \brief Handles user input
         */
        void ProcessInput()
        {
            auto& commands = world_.GetCommandQueue();

            sf::Event event;
            while (window_.pollEvent(event))
            {
                player_.HandleEvent(event, commands);

                switch (event.type)
                {
                case sf::Event::Closed:
                    window_.close();
                    break;
                case sf::Event::GainedFocus:
                    isPaused_ = false;
                    break;
                case sf::Event::LostFocus:
                    isPaused_ = true;
                    break;
                }
            }

            player_.HandleRealtimeInput(commands);
        }

        /**
         * \brief Updates the game logic ( everything that happens in the game)
         */
        void Update(sf::Time deltaTime)
        {
            world_.Update(deltaTime);
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
            world_.Draw();

            window_.setView(window_.getDefaultView());
            window_.display();
        }
    };
}
