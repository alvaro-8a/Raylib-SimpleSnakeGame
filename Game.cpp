#include "Game.h"
#include "Utils.h"
#include "raymath.h"


// Definition of shared variables and functions

Color game_utils::Orange{ 96, 204, 165, 255 };
Color game_utils::DarkOrange{ 24,51,41,255 };

bool game_utils::isElementInDeque(Vector2 element, std::deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i], element))
        {
            return true;
        }
    }

    return false;
}

Game::Game()
{    
}

void Game::Initialize()
{
    InitWindow(2 * mOffset + mCellSize * mCellCount, 2 * mOffset + mCellSize * mCellCount, "Retro Snake");
    SetTargetFPS(60);

    InitAudioDevice();
    mEatSound = LoadSound("Sounds/Coin.mp3");
    mWallSound = LoadSound("Sounds/Hit.mp3");
    mGameOver = LoadSound("Sounds/GameOver.mp3");

    pSnake = new Snake(mCellSize, mCellCount, mOffset);
    pFood = new Food(pSnake->body, mCellSize, mCellCount, mOffset);
}

void Game::RunLoop()
{
    while (!WindowShouldClose())
    {
        ProcessInput();

        if (EventTriggered(0.2))
        {
            UpdateGame();
        }
        Draw();
    }
}

void Game::Shutdown()
{
    UnloadSound(mEatSound);
    UnloadSound(mWallSound);
    UnloadSound(mGameOver);
    CloseAudioDevice();
    CloseWindow();
}

void Game::ProcessInput()
{

    if (IsKeyPressed(KEY_UP) && pSnake->direction.y != 1)
    {
        pSnake->direction = { 0, -1 };
        bRunning = true;
    }

    if (IsKeyPressed(KEY_DOWN) && pSnake->direction.y != -1)
    {
        pSnake->direction = { 0, 1 };
        bRunning = true;
    }

    if (IsKeyPressed(KEY_LEFT) && pSnake->direction.x != 1)
    {
        pSnake->direction = { -1, 0 };
        bRunning = true;
    }

    if (IsKeyPressed(KEY_RIGHT) && pSnake->direction.x != -1)
    {
        pSnake->direction = { 1, 0 };
        bRunning = true;
    }
}

void Game::UpdateGame()
{
    if (bRunning)
    {
        pSnake->Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
    }
}

void Game::Draw()
{
    BeginDrawing();

    ClearBackground(game_utils::Orange);

    DrawRectangleLinesEx(Rectangle{ (float)mOffset - 5, (float)mOffset - 5, (float)mCellCount * mCellSize + 10, (float)mCellCount * mCellSize + 10 }, 5, game_utils::DarkOrange);
    DrawText("Retro Snake", mOffset - 5, 20, 40, game_utils::DarkOrange);
    DrawText(TextFormat("%i", mScore), mOffset - 5, mOffset + mCellCount * mCellSize + 10, 40, game_utils::DarkOrange);
    
    pFood->Draw();
    pSnake->Draw();

    EndDrawing();
}

bool Game::EventTriggered(double interval)
{
    double currentTime = GetTime();

    if (currentTime - mLastUpdateTime >= interval)
    {
        mLastUpdateTime = currentTime;
        return true;
    }

    return false;
}

void Game::CheckCollisionWithFood()
{
    if (Vector2Equals(pSnake->body[0], pFood->position))
    {
        pSnake->bAddSegment = true;
        pFood->position = pFood->GenerateRandomPos(pSnake->body);
        mScore++;
        PlaySound(mEatSound);
    }
}

void Game::CheckCollisionWithEdges()
{
    if (pSnake->body[0].x >= mCellCount || pSnake->body[0].x < 0)
    {
        GameOver();
    }

    if (pSnake->body[0].y >= mCellCount || pSnake->body[0].y < 0)
    {
        GameOver();
    }
}

void Game::CheckCollisionWithTail()
{
    deque<Vector2> headlessBody = pSnake->body;
    headlessBody.pop_front();

    if (game_utils::isElementInDeque(pSnake->body[0], headlessBody))
    {
        GameOver();
    }
}

void Game::GameOver()
{
    pSnake->Reset();
    pFood->position = pFood->GenerateRandomPos(pSnake->body);
    bRunning = false;
    mScore = 0;
    PlaySound(mWallSound);
    PlaySound(mGameOver);
}