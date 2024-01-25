#pragma once

#include "raylib.h"
#include <vector>
#include <stdlib.h>

using namespace std;

enum direction : char {left, right, up, down};

void gameOverScreen()
{
    while(!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        DrawText("Game Over", 250, 250, 100, WHITE);

        EndDrawing();
    }
}

void winScreen()
{
    while(!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        DrawText("You Win!", 300, 250, 100, WHITE);

        EndDrawing();
    }
}

Color getRandomDiscernableColour()// Returns a random colour that is easy to see on a black background.
{
    struct Color colourToReturn = {0, 0, 0, 255};
    
    colourToReturn.r = rand() % 256;
    colourToReturn.g = rand() % 256;
    colourToReturn.b = rand() % 256;
    
    // Makes sure that the colour is easy to see. The colour is detected as too hard to see if all rgb components have values less than 175 because colours need to be vibrant to show up on a black background (light grey and white are exceptions to this rule). The colour is made more visible by maxxing out a random rgb component because, again, colours are most visible on a black background when they are vibrant.
    if(colourToReturn.r < 175 && colourToReturn.g < 175 && colourToReturn.b < 175)
    {
        switch(rand() % 3)
        {
            case 0:
                colourToReturn.r = 255;
                return colourToReturn;
            case 1:
                colourToReturn.g = 255;
                return colourToReturn;
            case 2:
                colourToReturn.b = 255;
                return colourToReturn;
        }
    }

    return colourToReturn;
}

class BreakoutBall
{
    private:
        Rectangle hitbox; //= {20, 20, 500, 500};// x, y, width, height
        Vector2 velocity;
        Color color;
        float maxXVelocity;
        bool shouldFlipXVelocity = false;
        bool shouldFlipYVelocity = false;

    public:
        BreakoutBall(float x, float y, float width, float height, float velX, float velY, Color ballColor, float maxXVel)
        {
            hitbox = {x, y, width, height};
            velocity = {velX, velY};
            color = ballColor;
            maxXVelocity = maxXVel;
        }
        
        // Update the ball's position based on its velocity. Returns true if breakout is done.
        bool update(float deltaTime, bool * playerWins, Rectangle paddleHitbox)
        {
            if(shouldFlipXVelocity)
            {
                velocity.x *= -1;
            }
            if(shouldFlipYVelocity)
            {
                velocity.y *= -1;
            }

            shouldFlipXVelocity = false;
            shouldFlipYVelocity = false;

            hitbox.x += velocity.x * deltaTime;
            hitbox.y += velocity.y * deltaTime;

            if(hitbox.y < 0)
            {
                gameOverScreen();

                *playerWins = false;

                return true;
            }
            
            else if(hitbox.y > GetScreenHeight() + 200)
            {
                *playerWins = true;

                return true;
            }

            else if(CheckCollisionRecs(hitbox, paddleHitbox) && velocity.y < 0)
            {
                velocity.y *= -1;

                velocity.x = maxXVelocity * (hitbox.x - paddleHitbox.x - (paddleHitbox.width/2) + (hitbox.width/2)) / ((paddleHitbox.width/2) + (hitbox.width/2));

                color = getRandomDiscernableColour();
            }

            if(hitbox.x < 0 || hitbox.x + hitbox.width > GetScreenWidth())
            {
                velocity.x *= -1;
            }
            return false;

            if (IsKeyDown(KEY_P))
            {
                velocity.y = 300;    
            }
        }

        //Render the ball
        void draw() 
        {
            DrawRectangleRec(hitbox, color);
        }

        //Getters for position and velocity
        Vector2 getPosition()
        {
            return {hitbox.x, hitbox.y};
        }

        Vector2 getVelocity()
        {
            return velocity;
        }

        Rectangle getHitbox()
        {
            return hitbox;
        }

        //Setters for position and velocity
        void setPosition(float x, float y)
        {
            hitbox.x = x;
            hitbox.y = y;
        }

        void setVelocity(float velX, float velY)
        {
            velocity.x = velX;
            velocity.y = velY;
        }

        void flipDirectionX()
        {
            shouldFlipXVelocity = true;
        }

        void flipDirectionY()
        {
            shouldFlipYVelocity = true;
        }

        //add other things later for brick and paddle collision

};

class BreakoutPaddle
{

    private:
            Rectangle hitbox; //= {20, 20, 500, 500};// x, y, width, height
            float speed;
            Color color;
    
    public:
            BreakoutPaddle(float x, float y, float width, float height, float paddleSpeed, Color paddleColor)
            {
                hitbox = {x, y, width, height};
                speed = paddleSpeed;
                color = paddleColor;
            }

            //user inputs for paddle
            void update(float deltaTime)
            {
                if (IsKeyDown(KEY_LEFT) && hitbox.x > 0)
                {
                    hitbox.x -= speed * deltaTime;
                }

                if (IsKeyDown(KEY_RIGHT) && hitbox.x + hitbox.width < GetScreenWidth())
                {
                    hitbox.x += speed * deltaTime;
                }

                
            }

            //draw the paddle
            void draw()
            {
                DrawRectangleRec(hitbox, color);
            }

            //get paddle position
            Vector2 getPosition()
            {
                return {hitbox.x, hitbox.y};
            }

            //get paddle dimensions
            Vector2 getSize()
            {
                return {hitbox.width, hitbox.height};
            }

            Rectangle getHitbox()
            {
                return hitbox;
            }

            //Setters for position and velocity
            void setPosition(float x, float y)
            {
                hitbox.x = x;
                hitbox.y = y;
            }

           
            
            

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
        float friction = 0;// Friction is the deceleration the player experiences when not pressing any buttons.
        float gravity;
        float maxXSpeed;
        float jumpSpeed;
        float coyoteTimerMax;
        float coyoteTimer = 0;

    public:
        PlatformerPlayer(Rectangle inHitbox, Color inColour, float inAirXAcceleration, float inGravity, float inMaxXSpeed, float inJumpSpeed, float inCoyoteTimerMax)
        {
            hitbox = inHitbox;
            colour = inColour;
            airXAcceleration = inAirXAcceleration;
            xAcceleration = inAirXAcceleration;
            gravity = inGravity;
            maxXSpeed = inMaxXSpeed;
            jumpSpeed = inJumpSpeed;
            coyoteTimerMax = inCoyoteTimerMax;
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

        void activateAirPhysics()// Sets friction and acceleration to what they should be when the player is airborne.
        {
            friction = 0;
            xAcceleration = airXAcceleration;
        }

        bool update()
        {
            // If the player is airborne: applies gravity, ensures the physics are correctly set, and decreaces the coyote timer.
            if(!grounded)
            {
                velocity.y += gravity * GetFrameTime();
                
                if(xAcceleration != airXAcceleration || friction != 0)// Activates air physics if they aren't already active, for when the player walks off a ledge.
                {
                    activateAirPhysics();
                }
                
                if(coyoteTimer > 0)
                {
                    coyoteTimer -= GetFrameTime();
                    
                    if(coyoteTimer < 0)
                    {
                        coyoteTimer = 0;
                    }
                }
            }

            // Alters the left/right velocity based on player input.
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
            // If the player isn't moving, applies friction.
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

            // Prevents the player from going over the speed cap.
            if(velocity.x > maxXSpeed)
            {
                velocity.x = maxXSpeed;
            }
            else if(velocity.x < -maxXSpeed)
            {
                velocity.x = -maxXSpeed;
            }

            // Jumping.
            if(IsKeyPressed(KEY_UP) && coyoteTimer > 0)
            {
                velocity.y = -jumpSpeed;

                colour = getRandomDiscernableColour();
                
                grounded = false;
                coyoteTimer = 0;
                activateAirPhysics();
            }

            // Moving the player based on its velocity.
            hitbox.x += velocity.x * GetFrameTime();
            hitbox.y += velocity.y * GetFrameTime();

            grounded = false;// Grounded will be set to true later this frame if the player is on top of a brick.

            // Handles touching the edge of the screen.
            if(hitbox.x < 0)// Prevents the player from moving off the left side.
            {
                hitbox.x = 0;

                if(velocity.x < 0) velocity.x = 0;
            }
            else if(hitbox.x + hitbox.width > GetScreenWidth())// If the player gets to the right edge, they win.
            {
                winScreen();

                return true;
            }
            else if(hitbox.y + hitbox.height > GetScreenHeight())// If the player hits the bottom of the screen, they lose.
            {
                gameOverScreen();

                return true;
            }

            return false;
        }

        void resetCoyoteTimer()
        {
            coyoteTimer = coyoteTimerMax;
        }

        void draw()
        {
            DrawRectangleRec(hitbox, colour);
        }
};

class Brick
{
    private:
        Rectangle hitbox;
        Color colour;
        float friction;
        float traction;

        direction rectangleEnteredFromSide(Rectangle otherHitbox, Vector2 otherVelocity)// Used if other was outside hitbox on the previous frame. up = top side, down = bottom side. Only works if you already know that other is touching hitbox already. otherVelocity must be in pixels per second, ensure that otherVelocity is the velocity other used for their last movement.
        {
            // Moving otherHitbox to where it was on the previous frame.
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

            return down;
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

        void updatePlatformer(PlatformerPlayer & player)
        {
            direction collisionSide;
            Rectangle playerHitbox = player.getHitbox();
            
            if(!CheckCollisionRecs(hitbox, playerHitbox))
            {
                if(playerHitbox.y + playerHitbox.height == hitbox.y)
                {
                    playerHitbox.y += 1;

                    if(CheckCollisionRecs(hitbox, playerHitbox))
                    {
                        player.setGrounded(true);
                    }
                }
                
                return;
            }

            collisionSide = rectangleEnteredFromSide(playerHitbox, player.getVelocity());

            switch(collisionSide)
            {
                case up:
                    player.setGrounded(true);

                    player.setYVelocity(0);
                    player.setYPosition(hitbox.y - playerHitbox.height);

                    player.setXAcceleration(traction);
                    player.setFriction(friction);

                    player.resetCoyoteTimer();
                    
                    return;
                    
                case left:
                    player.setXVelocity(0);
                    player.setXPosition(hitbox.x - playerHitbox.width);
                    
                    return;

                case right:
                    player.setXVelocity(0);
                    player.setXPosition(hitbox.x + hitbox.width);
                    
                    return;

                case down:
                    player.setYVelocity(0);
                    player.setYPosition(hitbox.y + hitbox.height);
                    
                    return;
            }
        }

        void updateBreakout(BreakoutBall & ball)
        {
            
        
            direction hitDirection;

            if(!CheckCollisionRecs(hitbox, ball.getHitbox()))
            {
                return;
            }

            hitDirection = rectangleEnteredFromSide(ball.getHitbox(), ball.getVelocity());

            if(hitDirection == left || hitDirection == right)
            {
                ball.flipDirectionX();
            }
            else
            {
                ball.flipDirectionY();
            }
            hitbox.x = -1000;

        } 
};