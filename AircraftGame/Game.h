#pragma once

#include "World.h"

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
                ProcessEvents();
                timeSinceLastUpdate += clock.restart();

                while (timeSinceLastUpdate > TIME_PER_FRAME)
                {
                    timeSinceLastUpdate -= TIME_PER_FRAME;

                    ProcessEvents();
                    if (!isPaused_)
                        Update(TIME_PER_FRAME);
                }

                Render();
            }
        }

    private:
        sf::RenderWindow window_;
        World world_;
        bool isMovingUp_ = false, isMovingDown_ = false, isMovingLeft_ = false, isMovingRight_ = false;
        bool isPaused_ = false;

        /**
         * \brief Handles user input
         */
        void ProcessEvents()
        {
            sf::Event event;
            while (window_.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::KeyPressed:
                    HandlePlayerInput(event.key.code, true);
                    break;
                case sf::Event::KeyReleased:
                    HandlePlayerInput(event.key.code, false);
                    break;
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
        }

        /**
         * \brief Updates the game logic ( everything that happens in the game)
         */
        void Update(sf::Time deltaTime)
        {
            world_.Update(deltaTime);

            /*sf::Vector2f movement(0.0f, 0.0f);

            if (isMovingUp_)
                movement.y -= PLAYER_SPEED;
            if (isMovingDown_)
                movement.y += PLAYER_SPEED;
            if (isMovingLeft_)
                movement.x -= PLAYER_SPEED;
            if (isMovingRight_)
                movement.x += PLAYER_SPEED;

            player_.move(movement * deltaTime.asSeconds());*/
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
            //window_.draw(player_);
            window_.display();
        }

        void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed)
        {
            if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
                isMovingUp_ = isPressed;
            else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
                isMovingDown_ = isPressed;
            else if (key == sf::Keyboard::A || key == sf::Keyboard::Left)
                isMovingLeft_ = isPressed;
            else if (key == sf::Keyboard::D || key == sf::Keyboard::Right)
                isMovingRight_ = isPressed;
        }
    };
}
