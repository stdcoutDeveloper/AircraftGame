#pragma once

#include <functional>
#include "SceneNode.h"

namespace AircraftGame
{
    enum CategoryType
    {
        NONE = 0,
        SCENE = 1 << 0,
        PLAYER_AIRCRAFT = 1 << 1,
        ALLIED_AIRCRAFT = 1 << 2,
        ENEMY_AIRCRAFT = 1 << 3
    };

    class SceneNode;

    struct Command
    {
        Command() : action_(), category_(NONE)
        {
        }

        /**
         * \brief The order issued to an object
         * @param SceneNode: a reference to a scene node, which is affected by the command
         * @param sf::Time: the delta time of the current frame
         */
        std::function<void(SceneNode&, sf::Time)> action_;

        CategoryType category_;
    };
}
