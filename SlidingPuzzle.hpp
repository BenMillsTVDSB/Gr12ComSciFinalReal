#include "GeneralHeader.hpp"
#include "Entity.hpp"
#include "raylib.h"

#include <iostream>
using namespace std;

bool mainSlidingPuzzle()// returns true if player clears section, false if they are defeated. Program ends upon returning false.
{
    // Gameplay loop
    vector<Entity> entities = 
    {Entity({0, 0, 150, 250}, 0, BLUE, "block"), 
    Entity({500, 50, 250, 150}, 0, BLUE, "block"), 
    Entity({850, 300, 150, 400}, 0, BLUE, "block"), 
    Entity({250, 150, 250, 150}, 0, BLUE, "block"),
    Entity({130, 350, 150, 150}, 0, BLUE, "block"),
    Entity({350, 300, 250, 200}, 0 , BLUE, "block"),
    Entity({300, 550, 100, 50}, 0, BLUE, "block"),
    Entity({650, 500, 150, 300}, 0, BLUE, "block"),
    Entity({730, 250, 70, 250}, 0, BLUE, "block"),
    Entity({0, 550, 50, 50}, 0, GREEN, "finish"),
    Entity({0, 0, 1000, 0}, 0, BLACK, "block"),
    Entity({1000, 0, 0, 600}, 0, BLACK, "block"),
    Entity({0, 600, 1000, 0}, 0, BLACK, "block"),
    Entity({0, 0, 0, 600}, 0, BLACK, "block")};

    Entity player({950, 0, 50, 50}, 5, WHITE, "player");
    float velocity = player.getVelocity();
    Vector2 movement = {0, 0};
    int counter = 20;
    int prevKeyPressed = -1;
    int currentKeyPressed = -1;
    bool keyPressedThisFrame;
    Rectangle rectangle;

    while(!WindowShouldClose())
    {
        keyPressedThisFrame = false;
        rectangle = player.getHitbox();
        // Update
        if (movement.x == 0 && movement.y == 0)
        {
            if (IsKeyDown(KEY_RIGHT)) 
            {
                movement = {velocity, 0};
                currentKeyPressed = KEY_RIGHT;
                keyPressedThisFrame = true;
                counter--;
            }  

            else if (IsKeyDown(KEY_LEFT)) 
            {
                movement = {-velocity, 0};
                currentKeyPressed = KEY_LEFT;
                keyPressedThisFrame = true;
                counter--;
            } 

            else if (IsKeyDown(KEY_DOWN)) 
            {
                movement = {0, velocity};
                currentKeyPressed = KEY_DOWN;
                keyPressedThisFrame = true;
                counter--;
            } 

            else if (IsKeyDown(KEY_UP)) 
            {
                movement = {0, -velocity};
                currentKeyPressed = KEY_UP;
                keyPressedThisFrame = true;
                counter--;
            }
        }

        rectangle.x += movement.x;
        rectangle.y += movement.y;

        player.setHitbox(rectangle);

        for(int i = 0; i < entities.size(); i++)
        {
            if (player.collidesWith(entities[i]) && entities[i].getType() == "block")
            {
                rectangle.x -= movement.x;
                rectangle.y -= movement.y;

                movement = {0, 0};

                player.setHitbox(rectangle);

                if(keyPressedThisFrame)
                {
                    counter++;
                }
            }
        }

        if (counter <= 0)
        {
            void gameOver();
        }

        for(int i = 0; i < entities.size(); i++)
        {
            DrawRectangleRec(entities[i].getHitbox(), entities[i].getColour());
        }

        BeginDrawing();

        ClearBackground(BLACK);
        DrawRectangleRec(player.getHitbox(), WHITE);

        DrawText(to_string(counter).c_str(), 10, 0, 100, WHITE);
        

        
        EndDrawing();

    }

    
    return false;
}
