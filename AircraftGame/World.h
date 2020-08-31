#pragma once

#include "Aircraft.h"
#include <array>
#include "SpriteNode.h"

namespace AircraftGame
{
    enum class WorldLayer
    {
        BACKGROUND,
        AIR,
        LAYER_COUNT
    };

    class World : private sf::NonCopyable
    {
    public:
        explicit World(sf::RenderWindow& window) : window_(window), worldView_(window_.getDefaultView()),
                                                   textures_(), sceneGraph_(), sceneLayers_(),
                                                   worldBounds_(0.0f, 0.0f, worldView_.getSize().x, 2000.0f),
                                                   spawnPosition_(worldView_.getSize().x / 2,
                                                                  worldBounds_.height - worldView_.getSize().y / 2),
                                                   scrollSpeed_(-50.0f),
                                                   playerAircraft_(nullptr)
        {
            LoadTextures();
            BuildScene();
            worldView_.setCenter(spawnPosition_);
        }

        void Update(sf::Time deltaTime)
        {
            worldView_.move(0.0f, scrollSpeed_ * deltaTime.asSeconds());

            sf::Vector2f position = playerAircraft_->getPosition();
            sf::Vector2f velocity = playerAircraft_->GetVelocity();
            if (position.x <= worldBounds_.left + 150 || position.x >= worldBounds_.left + worldBounds_.width - 150)
            {
                velocity.x = -velocity.x;
                playerAircraft_->SetVelocity(velocity);
            }

            sceneGraph_.Update(deltaTime);
        }

        void Draw()
        {
            window_.setView(worldView_);
            window_.draw(sceneGraph_);
        }

    private:
        sf::RenderWindow& window_;
        sf::View worldView_;
        TextureHolder textures_;
        SceneNode sceneGraph_;
        std::array<SceneNode*, static_cast<size_t>(WorldLayer::LAYER_COUNT)> sceneLayers_;

        sf::FloatRect worldBounds_;
        sf::Vector2f spawnPosition_;
        float scrollSpeed_;
        Aircraft* playerAircraft_;

        void LoadTextures()
        {
            textures_.LoadFromFile(TextureID::EAGLE, "../Resources/Textures/Eagle.png");
            textures_.LoadFromFile(TextureID::RAPTOR, "../Resources/Textures/Raptor.png");
            textures_.LoadFromFile(TextureID::DESERT, "../Resources/Textures/Desert.png");
        }

        void BuildScene()
        {
            for (size_t i = 0; i < sceneLayers_.size(); i++)
            {
                // create empty node represents a layer prepared for rendering
                SceneNode::SceneNodePtr layer(new SceneNode());
                sceneLayers_[i] = layer.get();

                sceneGraph_.AttachChildren(std::move(layer));
            }

            // tile the desert texture
            sf::Texture& texture = textures_.GetResource(TextureID::DESERT);
            sf::IntRect textureRect(worldBounds_); // convert to int
            texture.setRepeated(true);

            // sprite
            std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
            backgroundSprite->setPosition(worldBounds_.left, worldBounds_.top);
            sceneLayers_[static_cast<int>(WorldLayer::BACKGROUND)]->AttachChildren(std::move(backgroundSprite));

            // add the airplanes
            std::unique_ptr<Aircraft> leader(new Aircraft(AircraftType::EAGLE, textures_));
            playerAircraft_ = leader.get();
            playerAircraft_->setPosition(spawnPosition_);
            playerAircraft_->SetVelocity(40.0f, scrollSpeed_);
            sceneLayers_[static_cast<int>(Layer::AIR)]->AttachChildren(std::move(leader));

            // add 2 escorts
            std::unique_ptr<Aircraft> leftEscort(new Aircraft(AircraftType::RAPTOR, textures_));
            leftEscort->setPosition(-80.0f, 50.0f);
            playerAircraft_->AttachChildren(std::move(leftEscort));

            std::unique_ptr<Aircraft> rightEscort(new Aircraft(AircraftType::RAPTOR, textures_));
            rightEscort->setPosition(80.0f, 50.0f);
            playerAircraft_->AttachChildren(std::move(rightEscort));
        }
    };
}
