#pragma once

#include "StateStack.h"
#include "TitleState.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "ResourceHolder.h"
#include "Player.h"

namespace AircraftGame
{
    class Application
    {
    public:
        const sf::Time TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);

        Application() : window_(sf::VideoMode(640, 480), "States", sf::Style::Close), textures_(), fonts_(), player_(),
                        stateStack_(Context(window_, textures_, fonts_, player_))
        {
            textures_.LoadFromFile(TextureID::TITLE_SCREEN, "../Resources/Textures/TitleScreen.png");

            RegisterStates();
            stateStack_.PushState(StatesID::TITLE);
        }

        void Run()
        {
            sf::Clock clock;
            sf::Time timeSinceLastUpdate = sf::Time::Zero;

            while (window_.isOpen())
            {
                sf::Time deltaTime = clock.restart();
                timeSinceLastUpdate += deltaTime;

                while (timeSinceLastUpdate > TIME_PER_FRAME)
                {
                    timeSinceLastUpdate -= TIME_PER_FRAME;

                    ProcessInput();
                    Update(TIME_PER_FRAME);

                    if (stateStack_.IsEmpty())
                        window_.close();
                }

                Render();
            }
        }

    private:
        sf::RenderWindow window_;
        TextureHolder textures_;
        FontHolder fonts_;
        Player player_;
        StateStack stateStack_;

        void RegisterStates()
        {
            stateStack_.RegisterState<TitleState>(StatesID::TITLE);
            stateStack_.RegisterState<MenuState>(StatesID::MENU);
            stateStack_.RegisterState<GameState>(StatesID::GAME);
            stateStack_.RegisterState<PauseState>(StatesID::PAUSE);
        }

        void ProcessInput()
        {
            sf::Event event;
            while (window_.pollEvent(event))
            {
                stateStack_.HandleEvent(event);

                if (event.type == sf::Event::Closed)
                    window_.close();
            }
        }

        void Update(sf::Time deltaTime)
        {
            stateStack_.Update(deltaTime);
        }

        void Render()
        {
            window_.clear();
            stateStack_.Draw();

            window_.setView(window_.getDefaultView());

            window_.display();
        }
    };
}
