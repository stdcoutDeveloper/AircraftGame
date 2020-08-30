#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>
#include <cassert>

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
                throw std::runtime_error(
                    "[" + std::string(__FUNCTION__) + "@" + std::to_string(__LINE__) + "] Failed to load " + fileName);

            auto pair = textureMap_.insert(std::make_pair(id, std::move(texturePtr)));
            assert(pair.second);
        }

        sf::Texture& GetTexture(TextureID id)
        {
            auto itr = textureMap_.find(id);
            assert(itr != std::end(textureMap_));

            return *(itr->second);
        }

        const sf::Texture& GetTexture(TextureID id) const
        {
            auto itr = textureMap_.find(id);
            assert(itr != std::end(textureMap_));

            return *(itr->second);
        }

    private:
        typedef std::map<TextureID, std::unique_ptr<sf::Texture>> TextureMap;

        TextureMap textureMap_;
    };
}
