#include "Food.h"
#include "Utils.h"

using namespace std;

Food::Food(deque<Vector2> snakeBody, int cellSize, int cellCount, int offset)
    : mCellSize(cellSize),
    mCellCount(cellCount),
    mOffset(offset)
{
    Image image = LoadImage("Graphics/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    position = GenerateRandomPos(snakeBody);
}

Food::~Food()
{
    UnloadTexture(texture);
}

void Food::Draw()
{
    DrawTexture(texture, position.x * mCellSize + mOffset, position.y * mCellSize + mOffset, WHITE);
}

Vector2 Food::GenerateRandomPos(deque<Vector2> snakeBody)
{
    Vector2 position = GenerateRandomCell();

    while (game_utils::isElementInDeque(position, snakeBody))
    {
        position = GenerateRandomCell();
    }

    return position;
}

Vector2 Food::GenerateRandomCell()
{
    float x = GetRandomValue(0, mCellCount - 1);
    float y = GetRandomValue(0, mCellCount - 1);

    return Vector2{ x, y };
}