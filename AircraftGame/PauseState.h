#pragma once

#include "State.h"
#include "Utility.h"

namespace AircraftGame
{
    class PauseState : public State
    {
    public:
        PauseState(StateStack& stack, Context context) : State(stack, context), backgroundSprite_(), pausedText_(),
                                                         instructionText_()
        {
            sf::Font& font = context.fonts_->GetResource(FontsID::MAIN);
            sf::Vector2f viewSize = context.window_->getView().getSize();

            pausedText_.setFont(font);
            pausedText_.setString("Game Paused");
            pausedText_.setCharacterSize(70);
            CenterOrigin<sf::Text>(pausedText_);
            pausedText_.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

            instructionText_.setFont(font);
            instructionText_.setString("(Press Backspace to return to the main menu)");
            CenterOrigin<sf::Text>(instructionText_);
            instructionText_.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
        }

        void Draw() override
        {
            sf::RenderWindow& window = *(GetContext().window_);
            window.setView(window.getDefaultView());

            // darken what we see on the background
            sf::RectangleShape backgroundShape;
            backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
            backgroundShape.setSize(sf::Vector2f(window.getSize()));

            window.draw(backgroundShape);
            window.draw(pausedText_);
            window.draw(instructionText_);
        }

        bool Update(sf::Time deltaTime) override
        {
            return false;
        }

        bool HandleEvent(const sf::Event& event) override
        {
            if (event.type != sf::Event::KeyPressed)
                return false;

            // return to game if Escape is pressed again
            if (event.key.code == sf::Keyboard::Escape)
                RequestStackPop();

            // return to the main menu when Backspace is pressed
            if (event.key.code == sf::Keyboard::BackSpace)
            {
                RequestStateClear();
                RequestStackPush(StatesID::MENU);
            }

            return false;
        }

    private:
        sf::Sprite backgroundSprite_;
        sf::Text pausedText_;
        sf::Text instructionText_;
    };
}
