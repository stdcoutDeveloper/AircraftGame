#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>
#include <utility>
#include "Command.h"

namespace AircraftGame
{
    struct Command;

    enum class Layer
    {
        BACKGROUND,
        AIR,
        LAYERCOUNT // the total amount of layers
    };

    class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
    {
    public:
        typedef std::unique_ptr<SceneNode> SceneNodePtr;

        SceneNode() : childrens_(), parent_(nullptr)
        {
        }

        void AttachChildren(SceneNodePtr child)
        {
            child->parent_ = this;
            childrens_.push_back(std::move(child));
        }

        SceneNodePtr DetachChilren(const SceneNode& node)
        {
            auto itr = std::find_if(std::begin(childrens_), std::end(childrens_), [&node](SceneNodePtr& ptr) -> bool
            {
                return (ptr.get() == &node);
            });

            assert(itr != std::end(childrens_));

            SceneNodePtr result = std::move(*itr);
            result->parent_ = nullptr;
            childrens_.erase(itr);

            return result;
        }

        void Update(sf::Time deltaTime)
        {
            UpdateCurrentNode(deltaTime);

            UpdateChildren(deltaTime);
        }

        /**
         * \brief Get absolute transform
         */
        sf::Transform GetWorldTransform() const
        {
            // represent the identity transform (does nothing)
            sf::Transform transform = sf::Transform::Identity;

            for (const SceneNode* node = this; node != nullptr; node = node->parent_)
                transform = node->getTransform() * transform;

            return transform;
        }

        /**
         * \brief Get absolute position
         */
        sf::Vector2f GetWorldPosition() const
        {
            return GetWorldTransform() * sf::Vector2f();
        }

        virtual CategoryType GetCategory() const
        {
            return CategoryType::SCENE;
        }

        // execute command of player
        void OnCommand(const Command& command, sf::Time deltaTime)
        {
            if (command.category_ & GetCategory())
                command.action_(*this, deltaTime);

            for (const auto& e : childrens_)
                e->OnCommand(command, deltaTime);
        }

    private:
        std::vector<SceneNodePtr> childrens_;
        SceneNode* parent_; // not complete type so using pointer instead of object

        // overide draw() of sf::Drawable
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override final
        {
            // combine 2 transforms
            states.transform *= getTransform();

            // draw current object
            DrawCurrentNode(target, states);

            // draw children nodes
            DrawChildren(target, states);
        }

        /**
         * \brief Draw the current object (but not the children)
         */
        virtual void DrawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const
        {
        }

        virtual void DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const
        {
            for (const auto& ptr : childrens_)
                ptr->draw(target, states);
        }

        virtual void UpdateCurrentNode(sf::Time deltaTime)
        {
        }

        void UpdateChildren(sf::Time deltaTime)
        {
            for (const auto& ptr : childrens_)
                ptr->Update(deltaTime);
        }
    };
}
