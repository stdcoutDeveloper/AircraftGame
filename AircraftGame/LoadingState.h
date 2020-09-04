#pragma once

#include "State.h"
#include "ParallelTask.h"
#include "Utility.h"

namespace AircraftGame
{
    class LoadingState : public State
    {
    public:
        LoadingState(StateStack& stack, Context context) : State(stack, context)
        {
            sf::RenderWindow& window = *(GetContext().window_);
            sf::Font& font = context.fonts_->GetResource(FontsID::MAIN);
            sf::Vector2f viewSize = window.getView().getSize();

            loadingText_.setFont(font);
            loadingText_.setString("Loading Resources");
            CenterOrigin<sf::Text>(loadingText_);
            loadingText_.setPosition(viewSize.x / 2.0f, viewSize.y / 2.0f + 50.0f);

            progressBarBackground_.setFillColor(sf::Color::White);
            progressBarBackground_.setSize(sf::Vector2f(viewSize.x - 20, 10));
            progressBarBackground_.setPosition(10, loadingText_.getPosition().y + 40);

            progressBar_.setFillColor(sf::Color(100, 100, 100));
            progressBar_.setSize(sf::Vector2f(200, 10));
            progressBar_.setPosition(10, loadingText_.getPosition().y + 40);

            SetCompletion(0.0f);

            loadingTask_.Execute();
        }

        void Draw() override
        {
            sf::RenderWindow& window = *(GetContext().window_);
            window.setView(window.getDefaultView());

            window.draw(loadingText_);
            window.draw(progressBarBackground_);
            window.draw(progressBar_);
        }

        bool Update(sf::Time deltaTime) override
        {
            if (loadingTask_.IsFinished())
            {
                RequestStackPop();
                RequestStackPush(StatesID::GAME);
            }
            else
                SetCompletion(loadingTask_.GetCompletion());

            return true;
        }

        bool HandleEvent(const sf::Event& event) override
        {
            return true;
        }

        void SetCompletion(float percent)
        {
            if (percent > 1.0f)
                percent = 1.0f;

            progressBar_.setSize(sf::Vector2f(progressBarBackground_.getSize().x * percent, progressBar_.getSize().y));
        }

    private:
        sf::Text loadingText_;
        sf::RectangleShape progressBarBackground_;
        sf::RectangleShape progressBar_;

        ParallelTask loadingTask_;
    };
}
