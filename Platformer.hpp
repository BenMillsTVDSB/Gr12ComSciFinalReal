#include "GeneralHeader.hpp"// Problem: player is on the very edge of the brick when grounded, so they are ungrounded on the next frame. Coyote time will fix this.

void mainPlatformer()
{
    PlatformerPlayer player = PlatformerPlayer({10, 10, 40, 40}, WHITE, 700, 800, 600, 500, 0.4);
    vector<Brick*> bricks = {new Brick({20, 400, 200, 50}, BLUE, 1000, 700), new Brick({300, 400, 200, 50}, BLUE, 1000, 700)};
    bool playerOnBrickTop;

    // Gameplay loop
    while(!WindowShouldClose())
    {
        player.update();

        playerOnBrickTop = false;
        for(int i = 0; i < bricks.size(); i++)
        {
            if(bricks[i]->handleColisionPlatformer(player))
            {
                playerOnBrickTop = true;
            }
        }
        if(!playerOnBrickTop && player.getGrounded()) player.unground();

        BeginDrawing();

        ClearBackground(BLACK);

        player.draw();
        
        for(int i = 0; i < bricks.size(); i++)
        {
            bricks[i]->draw();
        }

        EndDrawing();
    }
}