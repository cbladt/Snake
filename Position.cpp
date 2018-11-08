#include "Position.hpp"

Position::Position(Position::position_t x, Position::position_t y) :
    _x(x),
    _y(y)
{}

Position::position_t Position::GetX() const
{
    return _x;
}

Position::position_t Position::GetY() const
{
    return _y;
}


