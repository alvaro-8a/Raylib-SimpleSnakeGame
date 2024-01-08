#include "Snake.h"
#include <raylib.h>
#include <deque>
#include "raymath.h"
#include "Utils.h"

using namespace std;

Snake::Snake(int cellSize, int cellCount, int offset)
    : mCellSize(cellSize), 
    mCellCount(cellCount), 
    mOffset(offset)
{
    body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} };
}

void Snake::Draw()
{
    for (unsigned int i = 0; i < body.size(); i++)
    {
        Rectangle rec{ (float)(body[i].x * mCellSize + mOffset), (float)(body[i].y * mCellSize + mOffset), (float)mCellSize, (float)mCellSize };
        DrawRectangleRounded(rec, .5, 6, game_utils::DarkOrange);
    }
}

void Snake::Update()
{
    body.push_front(Vector2Add(body[0], direction));

    if (bAddSegment)
    {
        bAddSegment = false;
    }
    else {
        body.pop_back();
    }
}

void Snake::Reset()
{
    body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} };
    direction = { 1, 0 };
}
