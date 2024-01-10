#pragma once// check back later, remove if this is unneeded.

#include "raylib.h"

enum gameMode : char {slidingPuzzle, breakout, platformer};// Potentially unnecessary

enum direction : char {left, right, up, down};

class Brick
{
    private:
        Rectangle hitbox; //= {20, 20, 500, 500};// x, y, width, height
        Color colour;

        direction rectangleEnteredFromSide(Rectangle otherHitbox, Vector2 otherVelocity)// Used if other was outside hitbox on the previous frame. up = top side, down = bottom side. Only works if you already know that other is touching hitbox already. otherVelocity must be in pixels per second, ensure that otherVelocity is the velocity other used for their last movement.
        {
            // moving otherHitbox to where it was on the previous frame.
            otherHitbox.y -= otherVelocity.y * GetFrameTime();
            otherHitbox.x -= otherVelocity.x * GetFrameTime();
            
            if(otherHitbox.y + otherHitbox.height <= hitbox.y)
            {
                return up;
            }
            if(otherHitbox.x >= hitbox.x + hitbox.width)
            {
                return right;
            }
            if(otherHitbox.x + otherHitbox.width <= hitbox.x)
            {
                return left;
            }
            if(otherHitbox.y <= hitbox.y + hitbox.height)
            {
                return down;
            }

            otherHitbox.x = 0/0;// If the game crashed and you ended up here, then there was a problem with either this code or how it was used. Let the group know.
        }

    public:
        Brick(Rectangle inHitbox, Color inColour)
        {
            hitbox = inHitbox;
            colour = inColour;
        }

        virtual void update() {}// Can be used if you need a subclass.

        
};

void gameOverScreen()
{
    while(!WindowShouldClose())
    {
        BeginDrawing();
        DrawText("Game Over", 250, 250, 100, WHITE);
        EndDrawing();
    }
}
