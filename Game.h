#pragma once
#include "Snake.h"
#include "Food.h"

class Game
{
public:
    Game();

    ~Game() {};

    void Initialize();

    void RunLoop();

    void Shutdown();

private:
    int mCellSize{ 30 };
    int mCellCount{ 25 };
    int mOffset{ 75 };
    double mLastUpdateTime = 0;

    bool bRunning = true;
    int mScore{ 0 };
    Sound mEatSound;
    Sound mWallSound;
    Sound mGameOver;

    Snake *pSnake;
    Food *pFood;

    void ProcessInput();

    void UpdateGame();
    
    void Draw();

    bool EventTriggered(double interval);

    void CheckCollisionWithFood();

    void CheckCollisionWithEdges();

    void CheckCollisionWithTail();

    void GameOver();
};

