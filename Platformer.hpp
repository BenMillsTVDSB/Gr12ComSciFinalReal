#include "GeneralHeader.hpp"

void mainPlatformer(vector<Brick> & bricks, clock_t startTime)// Ben.
{
    PlatformerPlayer player = PlatformerPlayer({5, -200, 20, 20}, WHITE, 500, 800, 250, 350, 0.2);

    // Gameplay loop
    while(!WindowShouldClose())
    {
        // Updating objects
        if(player.update(startTime)) return;

        for(int i = 0; i < bricks.size(); i++)
        {
            bricks[i].updatePlatformer(player);
        }

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