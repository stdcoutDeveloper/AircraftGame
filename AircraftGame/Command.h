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

    template <typename GameObject, typename Function>
    std::function<void(SceneNode&, sf::Time)> DerivedAction(Function function)
    {
        return [=](SceneNode& node, sf::Time deltaTime)
        {
            assert(dynamic_cast<GameObject*>(&node) != nullptr);

            function(static_cast<GameObject&>(node), deltaTime);
        };
    }
}
