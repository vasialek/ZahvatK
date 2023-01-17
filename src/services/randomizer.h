#pragma once

#ifdef ARDUINO
#else
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#endif

class Randomizer
{
private:
    int _directions[8];
    int _winds[3];
    int _lastDirections[3];
    int _totalDirections = 0;

    int GetRandomDirection();
    int GetRandomWind();
    bool IsSameDirectionRepeated(int direction);
    bool ShouldUseOtherDirection(int direction);
    bool IsDirectionTooFrequent(int direction);
    // int GetTotalDirections();
public:
    Randomizer();

    int GetDirection();
    void Dump();

    ~Randomizer();
};

inline int Randomizer::GetRandomDirection()
{
    return (rand() % 8);
}

inline int Randomizer::GetRandomWind()
{
    return (rand() % 3);
}

inline bool Randomizer::IsSameDirectionRepeated(int direction)
{
    // printf("Last directions: %d, %d, %d.\n", _lastDirections[0], _lastDirections[1], _lastDirections[2]);
    return _lastDirections[0] == direction &&
        _lastDirections[1] == direction &&
        _lastDirections[2] == direction;
}

inline bool Randomizer::ShouldUseOtherDirection(int direction)
{
    int currentDirectionTotal = _directions[direction];
    return IsSameDirectionRepeated(direction) ||
        IsDirectionTooFrequent(direction);
}

inline bool Randomizer::IsDirectionTooFrequent(int direction)
{
    if (_totalDirections < 24)
    {
        return false;
    }

    int minDirectionTimes = 999999;
    int minDirection = -1;
    for (auto i = 0; i < 8; i++)
    {
        if (i != direction && _directions[i] < minDirectionTimes)
        {
            minDirectionTimes = _directions[i];
            minDirection = i;
        }
    }

    // printf("Current direction %d was set %d times. Min direction %d was set - %d\n", direction, _directions[direction], minDirection, minDirectionTimes);
    auto directionPct = _directions[direction] * 100 / _totalDirections;
    auto minDirectionPct = minDirectionTimes * 100 / _totalDirections;
    // printf("Current direction %d%%, min direction %d%%\n", directionPct, minDirectionPct);
    return directionPct - minDirectionPct > 7;
}

// inline int Randomizer::GetTotalDirections()
// {
//     auto total = 0;
//     for (auto i = 0; i < 8; i++)
//     {
//         total += _directions[i];
//     }
    
//     return total;
// }

Randomizer::Randomizer()
{
    srand((unsigned)time(NULL));
    _directions[0] = _directions[1] = _directions[2] = _directions[3] = _directions[4] = _directions[5] = _directions[6] = _directions[7] = 0;
    _winds[0] = _winds[1] = _winds[2] = 0;

    _lastDirections[0] = _lastDirections[1] = _lastDirections[2] = -1;
}

inline int Randomizer::GetDirection()
{
    auto direction = GetRandomDirection();

    if (ShouldUseOtherDirection(direction))
    {
        direction = GetRandomDirection();
        // todo: generate random until it is not repeated?
        if (ShouldUseOtherDirection(direction))
        {
            direction = GetRandomDirection();
        }
    }
    
    _lastDirections[_totalDirections % 3] = direction;
    _directions[direction]++;
    _totalDirections++;
    return direction;
}

inline void Randomizer::Dump()
{
    printf("Direction total:\n");
    for (auto i = 0; i < 8; i++)
    {
        printf("  %d = %d\n", i, _directions[i]);
    }
}

Randomizer::~Randomizer()
{
}
