#ifndef POSITION_HPP
#define POSITION_HPP

#include <stdint.h>

class Position
{
public:
    using position_t = uint8_t;

    Position(position_t x, position_t y);
    ~Position() = default;

    position_t GetX() const;
    position_t GetY() const;

private:
    position_t _x;
    position_t _y;
};

#endif // POSITION_HPP
