#pragma once

#include "State.h"
#include "Utility.h"

namespace AircraftGame
{
    enum class OptionNames
    {
        PLAY,
        EXIT
    };

    class MenuState : public State
    {
    public:
        MenuState(StateStack& stack, Context context) : State(stack, context), options_(), optionIndex_(0)
        {
            sf::Texture& texture = context.textures_->GetResource(TextureID::TITLE_SCREEN);
            sf::Font& font = context.fonts_->GetResource(FontsID::MAIN);

            backgroundSprite_.setTexture(texture);

            sf::Text playOption;
            playOption.setFont(font);
            playOption.setString("Play");
            CenterOrigin<sf::Text>(playOption);
            playOption.setPosition(context.window_->getView().getSize() / 2.0f);
            options_.push_back(playOption);

            sf::Text exitOption;
            exitOption.setFont(font);
            exitOption.setString("Exit");
            CenterOrigin<sf::Text>(exitOption);
            exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.0f));
            options_.push_back(exitOption);

            UpdateOptionText();
        }

        void Draw() override
        {
            sf::RenderWindow& window = *(GetContext().window_);
            window.setView(window.getDefaultView());
            window.draw(backgroundSprite_);

            for (const auto& text : options_)
                window.draw(text);
        }

        bool Update(sf::Time deltaTime) override
        {
            return true;
        }

        bool HandleEvent(const sf::Event& event) override
        {
            if (event.type != sf::Event::KeyPressed)
                return false;

            if (event.key.code == sf::Keyboard::Return)
            {
                if (optionIndex_ == static_cast<size_t>(OptionNames::PLAY))
                {
                    RequestStackPop();
                    RequestStackPush(StatesID::GAME);
                }
                else if (optionIndex_ == static_cast<size_t>(OptionNames::EXIT))
                    RequestStackPop();
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                if (optionIndex_ > 0)
                    optionIndex_--;
                else
                    optionIndex_ = options_.size() - 1;

                UpdateOptionText();
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                if (optionIndex_ < options_.size() - 1)
                    optionIndex_++;
                else
                    optionIndex_ = 0;

                UpdateOptionText();
            }
        }

        void UpdateOptionText()
        {
            if (options_.empty())
                return;

            for (auto& text : options_)
                text.setColor(sf::Color::White);

            options_[optionIndex_].setColor(sf::Color::Red);
        }

    private:
        sf::Sprite backgroundSprite_;
        std::vector<sf::Text> options_;
        size_t optionIndex_;
    };
}
