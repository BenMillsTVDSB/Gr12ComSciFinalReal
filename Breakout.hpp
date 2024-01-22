#include "GeneralHeader.hpp"

bool mainBreakout(vector<Brick> & bricks)// returns true if player clears section, false if they are defeated. Program ends upon returning false.
{
    bool returnValue;
    BreakoutPaddle paddle = BreakoutPaddle(400, 100, 150, 25, 300, RED);
    BreakoutBall ball = BreakoutBall(400, 100, 20, 20, 200, 200, RED);
    bricks = {Brick({20, 400, 200, 50}, BLUE, 2000, 700), Brick({240, 400, 200, 50}, BLUE, 2000, 700), Brick({460, 400, 200, 50}, BLUE, 2000, 700), Brick({680, 400, 200, 50}, BLUE, 2000, 700), Brick({900, 400, 200, 50}, BLUE, 2000, 700)};
    
    
    // test
    // Gameplay loop
    while(!WindowShouldClose())
    {
        
        paddle.update(GetFrameTime());
        
        if(ball.update(GetFrameTime(), &returnValue))
        {
            return returnValue;
        }

        for(int i = 0; i < bricks.size(); i++)
        {
            bricks[i].updateBreakout(ball);
        }

        BeginDrawing();

        ClearBackground(BLACK);
        paddle.draw();
        ball.draw();

        for(int i = 0; i < bricks.size(); i++)
        {
            bricks[i].draw();
        }










        EndDrawing();
    }
    
    return false;
}