#pragma once

#include "State.h"
#include "Utility.h"

namespace AircraftGame
{
    class TitleState : public State
    {
    public:
        TitleState(StateStack& stack, Context context) : State(stack, context), backgroundSprite_(), text_(),
                                                         isShowText_(true), textEffectTime(sf::Time::Zero)
        {
            backgroundSprite_.setTexture(context.textures_->GetResource(TextureID::TITLE_SCREEN));

            text_.setFont(context.fonts_->GetResource(FontsID::MAIN));
            text_.setString("Press any key to start");
            CenterOrigin<sf::Text>(text_);
            text_.setPosition(context.window_->getView().getSize() / 2.0f);
        }

        void Draw() override
        {
            sf::RenderWindow& window = *(GetContext().window_);
            window.draw(backgroundSprite_);

            if (isShowText_)
                window.draw(text_);
        }

        // the blinking effect on the sf::Text object
        bool Update(sf::Time deltaTime) override
        {
            textEffectTime += deltaTime;

            if (textEffectTime >= sf::seconds(0.5f))
            {
                isShowText_ = !isShowText_;
                textEffectTime = sf::Time::Zero;
            }

            return true;
        }

        bool HandleEvent(const sf::Event& event) override
        {
            if (event.type == sf::Event::KeyPressed)
            {
                RequestStackPop();
                RequestStackPush(StatesID::MENU);
            }

            return true;
        }

    private:
        sf::Sprite backgroundSprite_;
        sf::Text text_;
        bool isShowText_;
        sf::Time textEffectTime;
    };
}
