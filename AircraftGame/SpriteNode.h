#pragma once

#include "SceneNode.h"

namespace AircraftGame
{
    class SpriteNode : public SceneNode
    {
    public:
        explicit SpriteNode(const sf::Texture& texture) : sprite_(texture)
        {
        }

        SpriteNode(const sf::Texture& texture, const sf::IntRect& rect) : sprite_(texture, rect)
        {
        }

    private:
        sf::Sprite sprite_;

        void DrawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            target.draw(sprite_, states);
        }
    };
}
