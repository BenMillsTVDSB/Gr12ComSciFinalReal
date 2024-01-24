#include "GeneralHeader.hpp"// TODO: comment the player's update function and the brick functions that I made. Claim my functions. Comment challenges.

void mainPlatformer(vector<Brick> & bricks)
{
    PlatformerPlayer player = PlatformerPlayer({10, 10, 20, 20}, WHITE, 500, 800, 250, 350, 0.2);

    // Gameplay loop
    while(!WindowShouldClose())
    {
        // Updating objects
        if(player.update()) return;

        for(int i = 0; i < bricks.size(); i++)
        {
            if(bricks[i].updatePlatformer(player))
            {
                player.setGrounded(true);
            }
        }
        
        player.checkIfShouldUnground();

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