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
        }

        bool Update(sf::Time deltaTime) override
        {
        }

        bool HandleEvent(const sf::Event& event) override
        {
        }

    private:
        World world_;
        Player& player_;
    };
}
