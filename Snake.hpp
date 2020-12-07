#pragma once

#define OLC_PGE_APPLICATION
#define OLC_GFX_OPENGL10
#include "olcPixelGameEngine.h"

#include <vector>
#include <map>

class GameOver :
        public std::exception
{
public:
    GameOver(std::string what) :
        _what(what)
    {}

    const char* what() const noexcept final override
    {
        return _what.c_str();
    }

private:
    std::string _what;
};

auto GetTimeMs()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

using Coordinates = std::pair<int, int>;

template <int screenWidth, int screenHeight, int pixelWidth, int pixelHeight>
class Snake :
        public olc::PixelGameEngine
{
public:
    Snake() :
        _currentDirection(Direction::North),
        _lastTickMs(GetTimeMs()),
        _tickCount(0),
        _run(true)
    {
        sAppName = "Snake";

        if (!Construct(screenWidth, screenHeight, pixelWidth, pixelHeight))
        {
            throw "Could not construct snake!";
        }

        Start();
    }

    bool OnUserCreate() final override
    {
        SetBackground(olc::BLACK);        
        CreateInitialSnake();
        return true;
    }

    bool OnUserUpdate(float) final override
    {
        try
        {
            if (_run)
            {
                DoOnUserUpdate();
            }
        }
        catch (GameOver&)
        {
            _run = false;
            DrawTheSnake(true);
        }

        return true;
    }

private:
    enum class Direction
    {
        North,
        East,
        South,
        West
    };

    std::vector<Coordinates> _snake;
    Direction _currentDirection;
    size_t _lastTickMs;
    size_t _tickCount;
    bool _run;

    void DoOnUserUpdate()
    {
        auto now = GetTimeMs();
        if (now - _lastTickMs > 100)
        {
            Tick();
            _lastTickMs = now;
            _tickCount++;
        }

        HandleInput();
    }

    template <typename T>
    void MoveNorth(T& x)
    {
        x--;
    }

    template <typename T>
    void MoveSouth(T& x)
    {
        x++;
    }

    template <typename T>
    void MoveEast(T& y)
    {
        y++;
    }

    template <typename T>
    void MoveWest(T& y)
    {
        y--;
    }

    template <typename T>
    void SetBackground(T& t)
    {
        for (int x = 0; x < ScreenWidth(); x++)
        {
            for (int y = 0; y < ScreenHeight(); y++)
            {                
                if (IsBorder(x, y))
                {
                    Draw(x, y, olc::GREY);
                }

                else
                {
                    Draw(x, y, t);
                }
            }
        }       
    }

    template <typename T>
    bool IsBorder(T x, T y)
    {
        if (x == 0)
        {
            return true;
        }

        else if (x == ScreenWidth() - 1)
        {
            return true;
        }

        else if (y == 0)
        {
            return true;
        }

        else if (y == ScreenHeight() - 1)
        {
            return true;
        }

        return false;
    }

    constexpr void HandleInput()
    {
        if (GetKey(olc::Key::UP).bReleased)
        {
            _currentDirection = Direction::North;
        }

        if (GetKey(olc::Key::RIGHT).bReleased)
        {
            _currentDirection = Direction::East;
        }

        if (GetKey(olc::Key::DOWN).bReleased)
        {
            _currentDirection = Direction::South;
        }

        if (GetKey(olc::Key::LEFT).bReleased)
        {
            _currentDirection = Direction::West;
        }
    }

    constexpr void Tick()
    {
        FollowTheSnakeHead();
        MoveTheSnakeHead();
        SetBackground(olc::BLACK);
        DrawTheSnake();

        if (_tickCount % 10 == 0)
        {
            AppendTheSnake();
        }
    }

    void CreateInitialSnake()
    {
        _snake.push_back(std::make_pair(screenWidth / 2, screenHeight / 2));
        _snake.push_back(std::make_pair(_snake.back().first, _snake.back().second+1));
        _snake.push_back(std::make_pair(_snake.back().first, _snake.back().second+1));
        _snake.push_back(std::make_pair(_snake.back().first, _snake.back().second+1));
        _snake.push_back(std::make_pair(_snake.back().first, _snake.back().second+1));
    }

    constexpr void AppendTheSnake()
    {
        auto last = _snake.back();

        switch (_currentDirection)
        {
            case Direction::North: MoveNorth(last.second); break;
            case Direction::East:  MoveEast(last.first); break;
            case Direction::South: MoveSouth(last.second); break;
            case Direction::West:  MoveWest(last.first); break;
        }

        _snake.push_back(last);
    }

    constexpr void DrawTheSnake(bool dead = false)
    {
        for (size_t n = 0; n < _snake.size(); n++)
        {            
            auto color = dead ? olc::RED : olc::GREEN;

            if (n == 0)
            {
                color = olc::VERY_DARK_GREEN;
            }

            auto& c = _snake.at(n);
            Draw(c.first, c.second, color);
        }
    }

    constexpr void MoveTheSnakeHead()
    {
        auto& head = _snake.front();

        switch (_currentDirection)
        {
            case Direction::North: MoveNorth(head.second); break;
            case Direction::East:  MoveEast(head.first); break;
            case Direction::South: MoveSouth(head.second); break;
            case Direction::West:  MoveWest(head.first); break;
        }

        CheckCollosion();
    }

    constexpr void CheckCollosion()
    {
        auto& head = _snake.front();

        for (size_t n = 1; n < _snake.size(); n++)
        {
            auto& c = _snake.at(n);

            if ((c.first == head.first) && (c.second == head.second))
            {
                throw GameOver("Collision");
            }

            if (IsBorder(head.first, head.second))
            {
                throw GameOver("Collision");
            }
        }
    }

    constexpr void FollowTheSnakeHead()
    {
        Coordinates last = {0,0};

        for (size_t n = 0; n < _snake.size(); n++)
        {
            if (n == 0)
            {
                last = _snake.at(n);
            }
            else
            {
                auto buffer = _snake.at(n);
                _snake[n] = last;
                last = buffer;
            }
        }
    }
};
