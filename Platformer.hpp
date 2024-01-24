#include "GeneralHeader.hpp"

void mainPlatformer(vector<Brick> & bricks)
{
    PlatformerPlayer player = PlatformerPlayer({10, 10, 20, 20}, WHITE, 700, 800, 300, 350, 0.2);
    bool playerOnBrickTop;

    // Gameplay loop
    while(!WindowShouldClose())
    {
        // Updating objects
        if(player.update()) return;

        playerOnBrickTop = false;
        for(int i = 0; i < bricks.size(); i++)
        {
            if(bricks[i].updatePlatformer(player))
            {
                playerOnBrickTop = true;
            }
        }
        if(!playerOnBrickTop && player.getGrounded()) player.unground();

        // Drawing objects
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("-->", 400, 50, 150, WHITE);

        player.draw();
        
        for(int i = 0; i < bricks.size(); i++)
        {
            bricks[i].draw();
        }

        EndDrawing();
    }
}