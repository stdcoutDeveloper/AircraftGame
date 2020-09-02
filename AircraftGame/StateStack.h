#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "State.h"

namespace AircraftGame
{
    enum class StatesID
    {
        NONE,
        TITLE,
        MENU,
        GAME,
        LOADING,
        PAUSE
    };

    enum class StateStackAction
    {
        PUSH,
        POP,
        CLEAR
    };

    struct PendingChange
    {
        StateStackAction action_;

        StatesID stateID_;
    };

    class StateStack : private sf::NonCopyable
    {
    public:
        explicit StateStack(Context context)
        {
        }

        template <typename T>
        void RegisterState(StatesID stateID)
        {
        }

        void Update(sf::Time deltaTime)
        {
        }

        void Draw()
        {
        }

        void HandleEvent(const sf::Event& event)
        {
        }

        void PushState(StatesID stateID)
        {
        }

        void PopState()
        {
        }

        void ClearStates()
        {
        }

        bool IsEmpty() const
        {
        }

    private:
        std::vector<StatePtr> stack_;
        std::vector<PendingChange> pendingList_;
        Context context_;
        std::map<StatesID, std::function<StatePtr()>> factories_;

        StatePtr CreateState(StatesID stateID)
        {
        }

        void ApplyPendingChanges()
        {
        }
    };
}
