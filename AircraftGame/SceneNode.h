#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>
#include <utility>

namespace AircraftGame
{
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

        SceneNode() : parent_(nullptr)
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
        virtual void DrawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const = 0;
        // pure virtual function?

        virtual void DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const
        {
            for (const auto& ptr : childrens_)
                ptr->draw(target, states);
        }
    };
}
