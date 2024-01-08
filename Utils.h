#pragma once

#include <raylib.h>
#include <deque>


namespace game_utils
{
    extern Color Orange;
    extern Color DarkOrange;

    extern bool isElementInDeque(Vector2 element, std::deque<Vector2> deque);
}