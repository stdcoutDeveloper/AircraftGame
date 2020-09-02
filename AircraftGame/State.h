#pragma once

#include <memory>
#include "StateStack.h"

namespace AircraftGame
{
    struct Context
    {
    };

    class StateStack;

    class State
    {
    public:
        State(StateStack& stack, Context context)
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
