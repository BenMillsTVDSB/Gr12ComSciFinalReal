#include "GeneralHeader.hpp"

bool mainBreakout(vector<Brick> & bricks)// returns true if player clears section, false if they are defeated. Program ends upon returning false.
{
    bool returnValue;
    BreakoutPaddle paddle = BreakoutPaddle(400, 100, 150, 25, 300, RED);
    BreakoutBall ball = BreakoutBall(400, 100, 20, 20, 200, 200, RED); //{x pos, y pos, width, height}
    bricks = {
        Brick({5, 305, 90, 50}, WHITE, 2000, 700), Brick({105, 305, 90, 50}, WHITE, 2000, 700), Brick({205, 305, 90, 50}, WHITE, 2000, 700), Brick({305, 305, 90, 50}, WHITE, 2000, 700), Brick({405, 305, 90, 50}, WHITE, 2000, 700), Brick({505, 305, 90, 50}, WHITE, 2000, 700), Brick({605, 305, 90, 50}, WHITE, 2000, 700), Brick({705, 305, 90, 50}, WHITE, 2000, 700), Brick({805, 305, 90, 50}, WHITE, 2000, 700), Brick({905, 305, 90, 50}, WHITE, 2000, 700),
        Brick({5, 365, 115, 50}, WHITE, 2000, 700), Brick({5, 365, 115, 50}, WHITE, 2000, 700), 
    };
    
    
    // test
    // Gameplay loop
    while(!WindowShouldClose())
    {
        
        paddle.update(GetFrameTime());
        
        if(ball.update(GetFrameTime(), &returnValue, paddle.getHitbox()))
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