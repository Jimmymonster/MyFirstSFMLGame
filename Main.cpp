#include "Game.h"

int main()
{
    //Initiate Game Engine
    Game game;

    while (game.isWindowOpen())
    {
        //Update
        game.UpdateDeltaTime();
        game.Update();

        //Render
        game.Render();

        //Framerate
        //game.Framerate();
    }
    return 0;
}