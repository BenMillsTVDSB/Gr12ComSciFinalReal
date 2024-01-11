#include "GeneralHeader.hpp"

void mainPlatformer()
{
    PlatformerPlayer player = PlatformerPlayer({10, 10, 40, 40}, WHITE, 400, 800, 99900, 500);
    Brick brick = Brick({20, 400, 200, 50}, BLUE, 700, 500);

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