#pragma once

#include "State.h"
#include "World.h"
#include "Player.h"

namespace AircraftGame
{
    class GameState : public State
    {
    public:
        GameState(StateStack& stack, Context context) : State(stack, context), world_(*(context.window_)),
                                                        player_(*(context.player_))
        {
        }

        void Draw() override
        {
            world_.Draw();
        }

        bool Update(sf::Time deltaTime) override
        {
            world_.Update(deltaTime);

            CommandQueue& commands = world_.GetCommandQueue();
            player_.HandleRealtimeInput(commands);

            return true;
        }

        bool HandleEvent(const sf::Event& event) override
        {
            CommandQueue& commands = world_.GetCommandQueue();
            player_.HandleEvent(event, commands);

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                RequestStackPush(StatesID::PAUSE);

            return true;
        }

    private:
        World world_;
        Player& player_;
    };
}
