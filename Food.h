#pragma once
#include "raylib.h"
#include <deque>

class Food
{
public:
    Vector2 position;
    Texture2D texture;

    Food(std::deque<Vector2> snakeBody, int cellSize, int cellCount, int offset);

    ~Food();

    void Draw();

    Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody);

private:
    int mCellSize;
    int mCellCount;
    int mOffset;

    Vector2 GenerateRandomCell();
};


