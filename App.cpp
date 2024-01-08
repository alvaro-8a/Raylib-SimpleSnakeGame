#include <iostream>
#include "Game.h"

int main() 
{
    Game game = Game();

    game.Initialize();
    game.RunLoop();
    game.Shutdown();

    return 0;
}