#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <cassert>
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
        explicit PendingChange(StateStackAction action, StatesID id = StatesID::NONE) : action_(action), stateID_(id)
        {
        }

        StateStackAction action_;
        StatesID stateID_;
    };

    class StateStack : private sf::NonCopyable
    {
    public:
        explicit StateStack(Context context) : stack_(), pendingList_(), context_(context), factories_()
        {
        }

        /**
         * \brief Register inside the stack all the states we may use
         * Do not create all the state objects from the beginning, 
         * since some of them may never exist
         */
        template <typename T>
        void RegisterState(StatesID stateID)
        {
            factories_.insert(std::make_pair(stateID, [this]() -> StatePtr
            {
                return StatePtr(new T(*this, context_));
            }));
        }

        void Update(sf::Time deltaTime)
        {
            for (auto itr = std::rbegin(stack_); itr != std::rend(stack_); ++itr)
            {
                if (!((*itr)->Update(deltaTime)))
                    break;
            }

            ApplyPendingChanges();
        }

        void Draw()
        {
            for (auto& element : stack_)
                element->Draw();
        }

        void HandleEvent(const sf::Event& event)
        {
            for (auto itr = std::rbegin(stack_); itr != std::rend(stack_); ++itr)
            {
                if (!((*itr)->HandleEvent(event)))
                    break;
            }

            ApplyPendingChanges();
        }

        void PushState(StatesID stateID)
        {
            pendingList_.push_back(PendingChange(StateStackAction::PUSH, stateID));
        }

        void PopState()
        {
            pendingList_.push_back(PendingChange(StateStackAction::POP));
        }

        void ClearStates()
        {
            pendingList_.push_back(PendingChange(StateStackAction::CLEAR));
        }

        bool IsEmpty() const
        {
            return stack_.empty();
        }

    private:
        std::vector<StatePtr> stack_;
        std::vector<PendingChange> pendingList_;
        Context context_;
        std::map<StatesID, std::function<StatePtr()>> factories_;

        StatePtr CreateState(StatesID stateID)
        {
            auto itr = factories_.find(stateID);
            assert(itr != std::end(factories_));

            return (itr->second)(); // invoking the stored std::function factory
        }

        void ApplyPendingChanges()
        {
            for (auto& change : pendingList_)
            {
                switch (change.action_)
                {
                case StateStackAction::PUSH:
                    stack_.push_back(CreateState(change.stateID_));
                    break;
                case StateStackAction::POP:
                    stack_.pop_back();
                    break;
                case StateStackAction::CLEAR:
                    stack_.clear();
                    break;
                }
            }

            pendingList_.clear();
        }
    };
}
