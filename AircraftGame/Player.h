#pragma once

#include "CommandQueue.h"
#include <iostream>

namespace AircraftGame
{
    // function object (functor)
    struct AircraftMover
    {
        AircraftMover(float velocityX, float velocityY) : velocity_(velocityX, velocityY)
        {
        }

        void operator()(Aircraft& aircraft, sf::Time) const
        {
            aircraft.Accelerate(velocity_);
        }

        sf::Vector2f velocity_;
    };

    enum class PlayerAction
    {
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,
        ACTION_COUNT
    };

    class Player
    {
    public:
        const float PLAYER_SPEED = 3.0f; // proper speed???

        Player()
        {
            keyBinding_[sf::Keyboard::Left] = PlayerAction::MOVE_LEFT;
            keyBinding_[sf::Keyboard::Right] = PlayerAction::MOVE_RIGHT;
            keyBinding_[sf::Keyboard::Up] = PlayerAction::MOVE_UP;
            keyBinding_[sf::Keyboard::Down] = PlayerAction::MOVE_DOWN;

            actionBinding_[PlayerAction::MOVE_LEFT].action_ = DerivedAction<Aircraft>(
                AircraftMover(-PLAYER_SPEED, 0.0f));
            actionBinding_[PlayerAction::MOVE_RIGHT].action_ = DerivedAction<Aircraft>(
                AircraftMover(PLAYER_SPEED, 0.0f));
            actionBinding_[PlayerAction::MOVE_UP].action_ = DerivedAction<Aircraft>(AircraftMover(0.0f, -PLAYER_SPEED));
            actionBinding_[PlayerAction::MOVE_DOWN].action_ = DerivedAction<Aircraft
            >(AircraftMover(0.0f, PLAYER_SPEED));

            for (auto& pair : actionBinding_)
                pair.second.category_ = PLAYER_AIRCRAFT;
        }

        void AssignKey(PlayerAction action, sf::Keyboard::Key key)
        {
            // check that no two keys map to the same action
            for (auto& pair : keyBinding_)
            {
                if (pair.second == action)
                    keyBinding_.erase(pair.first);
            }

            keyBinding_.insert(std::make_pair(key, action));
        }

        sf::Keyboard::Key GetAssignedKey(PlayerAction action) const
        {
            for (auto& pair : keyBinding_)
            {
                if (pair.second == action)
                    return pair.first;
            }

            return sf::Keyboard::Unknown;
        }

        // handle SFML events
        void HandleEvent(const sf::Event& event, CommandQueue& commands)
        {
            if (event.type == sf::Event::KeyPressed)
            {
                auto itr = keyBinding_.find(event.key.code);
                if (itr != std::end(keyBinding_) && !IsRealtimeAction(itr->second))
                    commands.Push(actionBinding_[itr->second]);
            }
        }

        /**
         * \brief Create a command every frame an arrow key is held down
         */
        void HandleRealtimeInput(CommandQueue& commands)
        {
            for (const auto& pair : keyBinding_)
            {
                if (sf::Keyboard::isKeyPressed(pair.first) && IsRealtimeAction(pair.second))
                    commands.Push(actionBinding_[pair.second]);
            }
        }

    private:
        std::map<sf::Keyboard::Key, PlayerAction> keyBinding_;
        std::map<PlayerAction, Command> actionBinding_;

        static bool IsRealtimeAction(PlayerAction action)
        {
            if (action == PlayerAction::MOVE_LEFT || action == PlayerAction::MOVE_RIGHT || action ==
                PlayerAction::MOVE_UP || action == PlayerAction::MOVE_DOWN)
                return true;

            return false;
        }
    };
}
