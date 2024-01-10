#include "GeneralHeader.hpp"
#include "raylib.h"

bool mainSlidingPuzzle()// returns true if player clears section, false if they are defeated. Program ends upon returning false.
{
    // Gameplay loop
    while(!WindowShouldClose())
    {
        BeginDrawing();
        InitWindow(400, 300, "SlidingPuzzle");
        SetTargetFPS(30);

        ClearBackground(RAYWHITE);
        DrawCircle(400, 0, 10, RED);
        DrawRectangle(400, 100, 50, 60, BLACK);

        //if(IsKeyPressed(KEY_LEFT))



        EndDrawing();

    }
    
    return false;
}