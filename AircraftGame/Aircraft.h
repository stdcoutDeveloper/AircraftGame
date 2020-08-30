#pragma once

#include "Entity.h"
#include "ResourceHolder.h"

namespace AircraftGame
{
    enum class AircraftType
    {
        EAGLE,
        RAPTOR
    };

    class Aircraft : public Entity
    {
    public:
        explicit Aircraft(AircraftType type, const TextureHolder& textures) : type_(type),
                                                                              sprite_(textures.GetResource(
                                                                                  GetTextureIDByAircraftType()))
        {
            // set origin of sprite to centre
            sf::FloatRect bounds = sprite_.getLocalBounds();
            sprite_.setOrigin(bounds.width / 2, bounds.height / 2);
        }

        void DrawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            target.draw(sprite_, states);
        }

    private:
        AircraftType type_;
        sf::Sprite sprite_;

        TextureID GetTextureIDByAircraftType() const
        {
            switch (type_)
            {
            case AircraftType::EAGLE:
                return TextureID::EAGLE;

            case AircraftType::RAPTOR:
                return TextureID::RAPTOR;
            }
        }
    };
}
