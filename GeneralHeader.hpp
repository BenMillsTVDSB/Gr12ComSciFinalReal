#pragma once// check back later, remove if this is unneeded.

#include "raylib.h"
#include <vector>

using namespace std;

enum gameMode : char {slidingPuzzle, breakout, platformer};// Potentially unnecessary

enum direction : char {left, right, up, down};

class breakoutBall
{
    private:
        Rectangle hitbox = {20, 20, 50, 50}; //= {20, 20, 500, 500};// x, y, width, height
        Vector2 velocity = {0, 0};
        Color color;

    public:
        



};




class PlatformerPlayer
{
    private:
        Rectangle hitbox;
        Vector2 velocity = {0, 0};
        Color colour;
        bool grounded = false;
        float xAcceleration;
        float airXAcceleration;
        float friction = 0;
        float gravity;
        float maxXSpeed;
        float jumpSpeed;

    public:
        PlatformerPlayer(Rectangle inHitbox, Color inColour, float inAirXAcceleration, float inGravity, float inMaxXSpeed, float inJumpSpeed)
        {
            hitbox = inHitbox;
            colour = inColour;
            airXAcceleration = inAirXAcceleration;
            xAcceleration = inAirXAcceleration;
            gravity = inGravity;
            maxXSpeed = inMaxXSpeed;
            jumpSpeed = inJumpSpeed;
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

        bool getGrounded()
        {
            return grounded;
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

        void setFriction(float inFriction)
        {
            friction = inFriction;
        }

        void unground()
        {
            grounded = false;
            friction = 0;
            xAcceleration = airXAcceleration;
        }

        void update()
        {
            if(IsKeyDown(KEY_LEFT) != IsKeyDown(KEY_RIGHT))
            {
                if(IsKeyDown(KEY_LEFT))
                {
                    velocity.x -= xAcceleration * GetFrameTime();
                }
                if(IsKeyDown(KEY_RIGHT))
                {
                    velocity.x += xAcceleration * GetFrameTime();
                }
            }
            else if(velocity.x > 0)
            {
                velocity.x -= friction * GetFrameTime();

                if(velocity.x < 0) velocity.x = 0;
            }
            else if(velocity.x < 0)
            {
                velocity.x += friction * GetFrameTime();

                if(velocity.x > 0) velocity.x = 0;
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
                    
                    unground();
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
        float traction;

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
        Brick(Rectangle inHitbox, Color inColour, float inTraction, float inFriction)
        {
            hitbox = inHitbox;
            colour = inColour;
            traction = inTraction;
            friction = inFriction;
        }

        void draw()
        {
            DrawRectangleRec(hitbox, colour);
        }

        virtual void update() {}// Can be used in subclases, will be called every frame.

        virtual bool handleColisionPlatformer(PlatformerPlayer & player)// returns true if player is on top of the brick.
        {
            direction collisionSide;
            
            if(!CheckCollisionRecs(hitbox, player.getHitbox())) return false;

            collisionSide = rectangleEnteredFromSide(player.getHitbox(), player.getVelocity());

            switch(collisionSide)
            {
                case up:
                    player.setGrounded(true);
                    player.setYVelocity(0);
                    player.setYPosition(hitbox.y - player.getHeight());
                    player.setXAcceleration(traction);
                    player.setFriction(friction);
                    
                    return true;
                case left:
                    player.setXVelocity(0);
                    player.setXPosition(hitbox.x - player.getWidth());
                    
                    return false;
                case right:
                    player.setXVelocity(0);
                    player.setXPosition(hitbox.x + hitbox.width);
                    
                    return false;
                case down:
                    player.setYVelocity(0);
                    player.setYPosition(hitbox.y + hitbox.height);
                    
                    return false;
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
