#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <Direction.hpp>

namespace Snake
{
    class Snake
    {
    public:
        Snake();
        void Move(Direction direction);
    };
} // Namespace Snake.

#endif // SNAKE_HPP
