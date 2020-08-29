#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

namespace AircraftGame
{
    enum class TextureID
    {
        LANDSCAPE,
        AIRPLANE,
        MISSILE
    };

    class TextureHolder
    {
    public:
        void LoadFromFile(TextureID id, const std::string& fileName)
        {
            auto texturePtr = std::make_unique<sf::Texture>();
            if (!texturePtr->loadFromFile(fileName))
            {
                // TODO: handle error
            }

            textureMap_.insert(std::make_pair(id, std::move(texturePtr)));
        }

        sf::Texture& GetTexture(TextureID id)
        {
            auto itr = textureMap_.find(id);
            if (itr == std::end(textureMap_))
            {
                // TODO: handle not found
            }

            return *(itr->second);
        }

        const sf::Texture& GetTexture(TextureID id) const
        {
            const auto itr = textureMap_.find(id);
            if (itr == std::cend(textureMap_))
            {
                // TODO: handle not found
            }

            return *(itr->second);
        }

    private:
        typedef std::map<TextureID, std::unique_ptr<sf::Texture>> TextureMap;

        TextureMap textureMap_;
    };
}
