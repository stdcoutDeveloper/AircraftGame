#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>
#include <cassert>

namespace AircraftGame
{
    /**
     * \brief Template for managing resources: textures, fonts and sound buffers. 
     */
    template <typename Resource, typename Identifier>
    class ResourceHolder
    {
    public:
        void LoadFromFile(Identifier id, const std::string& fileName)
        {
            auto resourcePtr = std::make_unique<Resource>();
            if (!resourcePtr->loadFromFile(fileName))
                throw std::runtime_error(
                    "[" + std::string(__FUNCTION__) + "@" + std::to_string(__LINE__) + "] Failed to load " + fileName);

            auto pair = resourceMap_.insert(std::make_pair(id, std::move(resourcePtr)));
            assert(pair.second);
        }

        /**
         * \brief Overload member function for sf::Shader specially
         */
        template <typename ParameterForShader>
        void LoadFromFile(Identifier id, const std::string& fileName, const ParameterForShader& secondParam)
        {
            auto resourcePtr = std::make_unique<Resource>();
            if (!resourcePtr->loadFromFile(fileName, secondParam))
                throw std::runtime_error(
                    "[" + std::string(__FUNCTION__) + "@" + std::to_string(__LINE__) + "] Failed to load " + fileName);

            auto pair = resourceMap_.insert(std::make_pair(id, std::move(resourcePtr)));
            assert(pair.second);
        }

        Resource& GetResource(Identifier id)
        {
            auto itr = resourceMap_.find(id);
            assert(itr != std::end(resourceMap_));

            return *(itr->second);
        }

        const Resource& GetResource(Identifier id) const
        {
            auto itr = resourceMap_.find(id);
            assert(itr != std::end(resourceMap_));

            return *(itr->second);
        }

    private:
        typedef std::map<Identifier, std::unique_ptr<Resource>> ResourceMap;

        ResourceMap resourceMap_;
    };

    enum class TextureID
    {
        EAGLE,
        RAPTOR
    };

    typedef ResourceHolder<sf::Texture, TextureID> TextureHolder;
}
