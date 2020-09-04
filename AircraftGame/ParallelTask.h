#pragma once

#include <SFML/System/Thread.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>

namespace AircraftGame
{
    class ParallelTask
    {
    public:
        ParallelTask() : thread_(&ParallelTask::RunTask, this), isFinished_(false)
        {
        }

        void Execute()
        {
            isFinished_ = false;
            elapsedTime_.restart();
            thread_.launch();
        }

        bool IsFinished()
        {
            // locking variables
            sf::Lock lock(mutex_);

            return isFinished_;
        }

        float GetCompletion()
        {
            sf::Lock lock(mutex_);

            return (elapsedTime_.getElapsedTime().asSeconds() / 10.0f);
        }

    private:
        sf::Thread thread_;
        bool isFinished_;
        sf::Clock elapsedTime_;
        sf::Mutex mutex_;

        void RunTask()
        {
            bool isEnded = false;
            while (!isEnded)
            {
                sf::Lock lock(mutex_);
                if (elapsedTime_.getElapsedTime().asSeconds() >= 10.0f)
                    isEnded = true;
            }

            {
                sf::Lock lock(mutex_);
                isFinished_ = true;
            }
        }
    };
}
