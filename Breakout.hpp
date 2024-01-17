#include "GeneralHeader.hpp"

bool mainBreakout(vector<Brick> & bricks)// returns true if player clears section, false if they are defeated. Program ends upon returning false.
{
    
    BreakoutPaddle paddle = BreakoutPaddle(400, 100, 150, 25, 300, RED);
    BreakoutBall ball = BreakoutBall(400, 100, 10, 10, 200, 200, RED);
    
    
    
    // test
    // Gameplay loop
    while(!WindowShouldClose())
    {
        
        paddle.update(GetFrameTime());
        ball.update(GetFrameTime());

        BeginDrawing();

        ClearBackground(BLACK);
        paddle.draw();
        ball.draw();












        EndDrawing();
    }
    
    return false;
}