#pragma once

#include <memory>
#include "StateStack.h"
#include "ResourceHolder.h"
#include "Player.h"

namespace AircraftGame
{
    /**
     * \biref Work as a holder of shared objects between all states of the game
     */
    struct Context
    {
        Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player) :
            window_(&window), textures_(&textures), fonts_(&fonts), player_(&player)
        {
        }

        sf::RenderWindow* window_;
        TextureHolder* textures_;
        FontHolder* fonts_;
        Player* player_;
    };

    class StateStack;

    class State
    {
    public:
        State(StateStack& stack, Context context) : stack_(&stack), context_(context)
        {
        }

        virtual ~State()
        {
        }

        virtual void Draw() = 0;

        virtual bool Update(sf::Time deltaTime) = 0;

        virtual bool HandleEvent(const sf::Event& event) = 0;

    protected:
        void RequestStackPush(StatesID stateID)
        {
        }

        void RequestStackPop()
        {
        }

        void RequestStateClear()
        {
        }

        Context GetContext() const
        {
        }

    private:
        StateStack* stack_;
        Context context_;
    };

    typedef std::unique_ptr<State> StatePtr;
}
