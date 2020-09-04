#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

namespace AircraftGame
{
    // T is sf::Sprite or sf::Text
    template <typename T>
    void CenterOrigin(T& obj)
    {
        sf::FloatRect bounds = obj.getLocalBounds();
        obj.setOrigin(std::floor(bounds.left + bounds.width / 2.0f), std::floor(bounds.top + bounds.height / 2.0f));
    }
}
