#pragma once
#include <raylib.h>
#include <deque>

using namespace std;

class Snake
{
public:
    deque<Vector2> body;
    Vector2 direction{ 1, 0 };
    bool bAddSegment = false;

    Snake(int cellSize, int cellCount, int offset);

    void Update();
    void Draw();
    void Reset();

private:
    int mCellSize;
    int mCellCount;
    int mOffset; 
};

