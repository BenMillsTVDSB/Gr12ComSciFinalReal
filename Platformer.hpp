#include "GeneralHeader.hpp"

void mainPlatformer()
{
    PlatformerPlayer player = PlatformerPlayer({10, 10, 40, 40}, WHITE, 700, 800, 600, 500);
    //vector<Brick*> = {};
    Brick brick = Brick({20, 400, 200, 50}, BLUE, 1000, 700);

    // Gameplay loop
    while(!WindowShouldClose())
    {
        player.update();
        brick.checkAndHandleColisionPlatformer(player);

        BeginDrawing();
        ClearBackground(BLACK);
        player.draw();
        brick.draw();
        EndDrawing();
    }
}