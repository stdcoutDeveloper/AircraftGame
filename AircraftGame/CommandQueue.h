#pragma once

#include <queue>
#include "Command.h"

namespace AircraftGame
{
    /**
     * \brief Transport commands to the world and the scene graph
     */
    class CommandQueue
    {
    public:
        void Push(const Command& command)
        {
            queue_.push(command);
        }

        Command Pop()
        {
            auto result = queue_.front();
            queue_.pop();

            return result;
        }

        bool IsEmpty() const
        {
            return queue_.empty();
        }

    private:
        std::queue<Command> queue_;
    };
}
