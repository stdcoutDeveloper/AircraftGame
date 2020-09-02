#pragma once

#include "SceneNode.h"

namespace AircraftGame
{
    class Entity : public SceneNode
    {
    public:
        void SetVelocity(sf::Vector2f velocity)
        {
            velocity_ = velocity;
        }

        void SetVelocity(float velocityX, float velocityY)
        {
            velocity_.x = velocityX;
            velocity_.y = velocityY;
        }

        sf::Vector2f GetVelocity() const
        {
            return velocity_;
        }

        void Accelerate(sf::Vector2f velocity)
        {
            velocity_ += velocity;
        }

        void Accelerate(float velocityX, float velocityY)
        {
            velocity_.x += velocityX;
            velocity_.y += velocityY;
        }

    private:
        sf::Vector2f velocity_;

        void UpdateCurrentNode(sf::Time deltaTime) override
        {
            // method of Transformable
            move(velocity_ * deltaTime.asSeconds());
        }
    };
}
