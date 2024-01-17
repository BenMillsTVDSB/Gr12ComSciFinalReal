#include "GeneralHeader.hpp"
#include "Entity.hpp"
#include "raylib.h"

bool mainSlidingPuzzle()// returns true if player clears section, false if they are defeated. Program ends upon returning false.
{
    // Gameplay loop
    vector<Entity> entities = {Entity({0, 0, 150, 250}, 0, BLUE), 
    Entity({500, 50, 250, 150}, 0, BLUE), 
    Entity({850, 300, 150, 400}, 0, BLUE), 
    Entity({250, 150, 250, 150}, 0, BLUE),
    Entity({130, 350, 150, 150}, 0, BLUE),
    Entity({350, 300, 250, 200}, 0 , BLUE),
    Entity({300, 550, 100, 50}, 0, BLUE),
    Entity({650, 500, 150, 300}, 0, BLUE),
    Entity({730, 250, 70, 250}, 0, BLUE),
    Entity({0, 0, 1000, 0}, 0, BLACK),
    Entity({1000, 0, 0, 600}, 0, BLACK),
    Entity({0, 600, 1000, 0}, 0, BLACK),
    Entity({0, 0, 0, 600}, 0 , BLACK)};

    Entity player({950, 0, 50, 50}, 5, WHITE);
    float velocity = player.getVelocity();
    Vector2 movement = {0, 0};

    while(!WindowShouldClose())
    {

        Rectangle rectangle = player.getHitbox();
        // Update
        if (movement.x == 0 && movement.y == 0)
        {
            if (IsKeyDown(KEY_RIGHT)) 
            {
                movement = {velocity, 0};
            }  

            else if (IsKeyDown(KEY_LEFT)) 
            {
                movement = {-velocity, 0};
            } 

            else if (IsKeyDown(KEY_DOWN)) 
            {
                movement = {0, velocity};
            } 

            else if (IsKeyDown(KEY_UP)) 
            {
                movement = {0, -velocity};
            }
        }

        rectangle.x += movement.x;
        rectangle.y += movement.y;

        player.setHitbox(rectangle);

        for(int i = 0; i < entities.size(); i++)
        {
            if (player.collidesWith(entities[i]))
            {
                rectangle.x -= movement.x;
                rectangle.y -= movement.y;

                movement = {0, 0};

                player.setHitbox(rectangle);
            }
        }

        for(int i = 0; i < entities.size(); i++)
        {
            DrawRectangleRec(entities[i].getHitbox(), entities[i].getColour());
        }

        BeginDrawing();

        ClearBackground(BLACK);
        DrawRectangleRec(player.getHitbox(), WHITE);
        
        EndDrawing();

    }
    
    return false;
}
