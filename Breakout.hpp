#include "GeneralHeader.hpp"

bool mainBreakout(vector<Brick> & bricks)// Owen - returns true if player clears section, false if they are defeated. Program ends upon returning false.
{
    bool returnValue;
    BreakoutPaddle paddle = BreakoutPaddle(400, 100, 150, 25, 300, RED);
    BreakoutBall ball = BreakoutBall(480, 280, 20, 20, -100, -200, RED, 400); //{x pos, y pos, width, height}
    bricks = {
        Brick({5, 305, 90, 50}, WHITE, 1500, 700), Brick({105, 305, 90, 50}, WHITE, 1500, 700), Brick({205, 305, 90, 50}, WHITE, 1500, 700), Brick({305, 305, 90, 50}, BLUE, 700, 150), Brick({405, 305, 90, 50}, WHITE, 1500, 700), Brick({505, 305, 90, 50}, WHITE, 1500, 700), Brick({605, 305, 90, 50}, WHITE, 1500, 700), Brick({705, 305, 90, 50}, BLUE, 700, 150), Brick({805, 305, 90, 50}, WHITE, 1500, 700), Brick({905, 305, 90, 50}, WHITE, 1500, 700),
        Brick({5, 365, 115, 50}, WHITE, 1500, 700), Brick({130, 365, 115, 50}, BLUE, 700, 150), Brick({255, 365, 115, 50}, WHITE, 1500, 700), Brick({380, 365, 115, 50}, BLUE, 700, 150), Brick({505, 365, 115, 50}, WHITE, 1500, 700), Brick({630, 365, 115, 50}, WHITE, 1500, 700), Brick({755, 365, 115, 50}, WHITE, 1500, 700), Brick({880, 365, 115, 50}, WHITE, 1500, 700), 
        Brick({5, 425, 190, 50}, WHITE, 1500, 700), Brick({205, 425, 190, 50}, BLUE, 700, 150), Brick({405, 425, 190, 50}, WHITE, 1500, 700), Brick({605, 425, 190, 50}, BLUE, 700, 150), Brick({805, 425, 190, 50}, WHITE, 1500, 700), 
        Brick({5, 485, 240, 50}, WHITE, 1500, 700), Brick({255, 485, 240, 50}, WHITE, 1500, 700), Brick({505, 485, 240, 50}, BLUE, 700, 150), Brick({755, 485, 240, 50}, WHITE, 1500, 700), 
        Brick({5, 545, 990, 50}, WHITE, 1500, 700)
    };
    
    
    // test
    // Gameplay loop
    while(!WindowShouldClose())
    {
        
        //updating functions running
        paddle.update(GetFrameTime()); 
        
        if(ball.update(GetFrameTime(), &returnValue, paddle.getHitbox())) 
        {
            return returnValue;
        }

        for(int i = 0; i < bricks.size(); i++) 
        {
            bricks[i].updateBreakout(ball);
        }

        //drawing loops
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