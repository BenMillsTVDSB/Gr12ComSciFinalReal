#pragma once// check back later, remove if this is unneeded.

#include "raylib.h"

enum gameMode : char {slidingPuzzle, breakout, platformer};// Potentially unnecessary

enum direction : char {left, right, up, down};

class PlatformerPlayer
{
    private:
        Rectangle hitbox;
        Vector2 velocity;
        Color colour;
        bool grounded = false;
        float xAcceleration;
        float airXAcceleration = 100;
        float gravity = 30;
        float maxXSpeed = 9999;
        float jumpSpeed = 100;

    public:
        PlatformerPlayer(Rectangle inHitbox, Vector2 inVelocity, Color inColour)
        {
            hitbox = inHitbox;
            velocity = inVelocity;
            colour = inColour;
            xAcceleration = airXAcceleration;
        }

        Rectangle getHitbox()
        {
            return hitbox;
        }

        void setYPosition(float inYPosition)
        {
            hitbox.y = inYPosition;
        }

        void setXPosition(float inXPosition)
        {
            hitbox.x = inXPosition;
        }

        float getHeight()
        {
            return hitbox.height;
        }

        float getWidth()
        {
            return hitbox.width;
        }

        Vector2 getVelocity()
        {
            return velocity;
        }

        void setYVelocity(float inYVelocity)
        {
            velocity.y = inYVelocity;
        }

        void setXVelocity(float inXVelocity)
        {
            velocity.x = inXVelocity;
        }

        void setGrounded(bool inGrounded)
        {
            grounded = inGrounded;
        }

        void setXAcceleration(float inXAcceleration)
        {
            xAcceleration = inXAcceleration;
        }

        void update()
        {
            if(IsKeyDown(KEY_LEFT))
            {
                velocity.x -= xAcceleration * GetFrameTime();
            }
            if(IsKeyDown(KEY_RIGHT))
            {
                velocity.x += xAcceleration * GetFrameTime();
            }

            if(velocity.x > maxXSpeed)
            {
                velocity.x = maxXSpeed;
            }
            else if(velocity.x < -maxXSpeed)
            {
                velocity.x = -maxXSpeed;
            }

            if(grounded)
            {
                if(IsKeyPressed(KEY_UP))
                {
                    velocity.y = -jumpSpeed;
                    grounded = false;

                    xAcceleration = airXAcceleration;
                }
            }
            else
            {
                velocity.y += gravity * GetFrameTime();
            }

            hitbox.x += velocity.x * GetFrameTime();
            hitbox.y += velocity.y * GetFrameTime();
        }

        void draw()
        {
            DrawRectangleRec(hitbox, colour);
        }
};

class Brick
{
    private:
        Rectangle hitbox; //= {20, 20, 500, 500};// x, y, width, height
        Color colour;
        float friction;

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

            otherHitbox.x = 0/0;// If the game crashed and you ended up here, then there was a problem with either this method or how it was called. Tell group.
        }

    public:
        Brick(Rectangle inHitbox, Color inColour, float inFriction)
        {
            hitbox = inHitbox;
            colour = inColour;
            friction = inFriction;
        }

        virtual void update() {}// Can be used in subclases, will be called every frame.

        virtual void checkAndHandleColisionPlatformer(PlatformerPlayer player)
        {
            direction collisionSide;
            
            if(!CheckCollisionRecs(hitbox, player.getHitbox())) return;

            collisionSide = rectangleEnteredFromSide(player.getHitbox(), player.getVelocity());

            switch(collisionSide)
            {
                case up:
                    player.setGrounded(true);
                    player.setYVelocity(0);
                    player.setYPosition(hitbox.y - player.getHeight());
                    player.setXAcceleration(friction);
                    break;
                case left:
                    player.setXVelocity(0);
                    player.setXPosition(hitbox.x - player.getWidth());
                    break;
                case right:
                    player.setXVelocity(0);
                    player.setXPosition(hitbox.x + hitbox.width);
                    break;
                case down:
                    player.setYVelocity(0);
                    player.setYPosition(hitbox.y + hitbox.height);
                    break;
            }
        }
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
