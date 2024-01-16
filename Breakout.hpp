#include "GeneralHeader.hpp"

bool mainBreakout(vector<Brick> & bricks)// returns true if player clears section, false if they are defeated. Program ends upon returning false.
{
    
    BreakoutPaddle paddle = BreakoutPaddle(400, 100, 150, 25, 300, RED);
    
    
    
    // test
    // Gameplay loop
    while(!WindowShouldClose())
    {
        
        paddle.update(GetFrameTime());
        
        BeginDrawing();

        ClearBackground(BLACK);
        paddle.draw();













        EndDrawing();
    }
    
    return false;
}