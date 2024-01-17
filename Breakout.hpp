#include "GeneralHeader.hpp"

bool mainBreakout(vector<Brick> & bricks)// returns true if player clears section, false if they are defeated. Program ends upon returning false.
{
    bool returnValue;
    BreakoutPaddle paddle = BreakoutPaddle(400, 100, 150, 25, 300, RED);
    BreakoutBall ball = BreakoutBall(400, 100, 20, 20, 200, 200, RED);
    
    
    
    // test
    // Gameplay loop
    while(!WindowShouldClose())
    {
        
        paddle.update(GetFrameTime());
        
        if(ball.update(GetFrameTime(), &returnValue))
        {
            return returnValue;
        }

        BeginDrawing();

        ClearBackground(BLACK);
        paddle.draw();
        ball.draw();












        EndDrawing();
    }
    
    return false;
}